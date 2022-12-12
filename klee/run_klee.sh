#!/bin/bash
#
# MIT License
#
# Copyright (c) 2022.  - BME-Crysys-HITMan
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

echo "KLEE runner utility for HITMan team klee testing by Daniel Abraham"
echo

if [ "$#" -lt "2" ]; then
  echo "Usage: $0 /path/to/build_dir /path/to/src/klee_dir [... target params ...]"
  echo
  echo "Example run ./run_klee.sh /code/build_klee /code/klee"
  echo
  echo
  exit 1
fi

SRC="$2"
BLD="$1"
shift
shift

if [ ! -d "$SRC" -o ! -f "$SRC/CMakeLists.txt" ]
then
  echo "[-] Error: source not found or not contains CMakeList"
  exit 1
fi

if [ -d "$BLD" ]
then
  echo "Cleaning build dir"
  rm -r "$BLD"/*
fi

if [ ! -d "$BLD" ]
then
  echo "Creating build dir at $BLD"
  mkdir "$BLD"
fi

echo "Setting variables"
export LLVM_COMPILER=clang
export LLVM_COMPILER_PATH=/usr/lib/llvm-11/bin
export LIBCXX_LIB=/tmp/libc++-install-110/lib/
export LIBCXX_ABI_LIB=/tmp/libc++-install-110/lib/
export LIBCXX_INC_DIR=/tmp/libc++-install-110/include/c++/v1/
export CXX_FLAGS="-nostdinc++ -stdlib=libc++ -lc++ -lc++abi -I$LIBCXX_INC_DIR -L$LIBCXX_LIB"

echo "Building"

CC=wllvm CXX=wllvm++ cmake -DCMAKE_CXX_FLAGS="$CXX_FLAGS" -S $SRC -B $BLD
make CAFF_Processor --directory=$BLD
extract-bc -o "$BLD/CAFF_Processor.bc" "$BLD/CAFF_Processor"

echo "Running KLEE"
# --max-time=3h30min
klee --only-output-states-covering-new --libcxx \
--libc=uclibc --posix-runtime --optimize \
--max-solver-time=1min --search=dfs \
--search=nurs:md2u --max-time=3h30min \
"$BLD/CAFF_Processor.bc" A --sym-files 1 120 "--getThumbnail" /code/output --sym-stdout

echo 'Building application'
rm -r /code/build-obj
mkdir /code/build-obj
cmake -DCMAKE_CXX_FLAGS="--coverage -fprofile-arcs -ftest-coverage" -S "$SRC" -B /code/build-obj
make CAFF_Processor --directory=/code/build-obj

echo 'Running application'
# shellcheck disable=SC2035
rm -f *.gcda
klee-replay /code/build-obj/CAFF_Processor "$BLD"/klee-last/*.ktest


echo 'Collect coverage'
rm -r /code/coverage

mkdir /code/coverage
cd /code/coverage || exit

# shellcheck disable=SC2038
find /code/build-obj -name '*.o' | xargs gcov --preserve-paths
