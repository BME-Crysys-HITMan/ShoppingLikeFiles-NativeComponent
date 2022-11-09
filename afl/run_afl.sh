#!/bin/sh
#
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
# Example run ./run_afl.sh /build/slf /code/afl

echo "AFL runner utility for HITman team afl testing by Daniel Abraham"
echo

if [ "$#" -lt "2" ]; then
  echo "Usage: $0 /path/to/build_dir /path/to/src_dir [... target params...]"
  echo
  echo "Example run ./run_afl.sh /build/slf /code/afl"
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

#export AFL_USE_ASAN=1
#export AFL_USE_MSAN=1
export AFL_USE_UBSAN=1

echo 'Running command cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ ..'

cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ -S $SRC -B $BLD

# cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ -S . -B ./build

make --directory=$BLD

#rm -r "/test/output/*"

afl-fuzz -i /test/inputs -o /test/output -D -- "$BLD"/afl_test @@

#"$BLD"/afl_test /test/inputs/1.caff