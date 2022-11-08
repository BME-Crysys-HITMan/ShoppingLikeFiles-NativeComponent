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
# /test/output/default/crashes
# /code/afl/error_cases
cp id:000000,sig:07,src:000000,time:3982,execs:125,op:flip1,pos:0 /code/afl/error_cases/1.caff
cp id:000001,sig:11,src:000000,time:4063,execs:127,op:flip1,pos:0 /code/afl/error_cases/2.caff
cp id:000002,sig:07,src:000000,time:8467,execs:413,op:flip1,pos:29 /code/afl/error_cases/3.caff
cp id:000003,sig:04,src:000000,time:161672,execs:4839,op:arith8,pos:1,val:-20 /code/afl/error_cases/4.caff
cp id:000004,sig:04,src:000000,time:282841,execs:9597,op:arith8,pos:85,val:-27 /code/afl/error_cases/5.caff
cp id:000005,sig:07,src:000000+000044,time:1014131,execs:33841,op:splice,rep:8 /code/afl/error_cases/6.caff
cp id:000006,sig:11,src:000057,time:1121503,execs:72305,op:flip1,pos:0 /code/afl/error_cases/7.caff
cp id:000007,sig:11,src:000063,time:1222517,execs:108650,op:flip1,pos:1 /code/afl/error_cases/8.caff
cp id:000008,sig:11,src:000063,time:1222547,execs:108661,op:flip1,pos:2 /code/afl/error_cases/9.caff
cp id:000009,sig:11,src:000063,time:1224698,execs:109084,op:arith8,pos:2,val:-11 /code/afl/error_cases/10.caff
cp id:000010,sig:11,src:000062,time:1533299,execs:134097,op:flip1,pos:0 /code/afl/error_cases/11.caff
#
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
#export AFL_USE_MSAN=0
export AFL_USE_UBSAN=1

echo 'Running command cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ ..'

cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ -S $SRC -B $BLD

# cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ -S . -B ./build

make --directory=$BLD

afl-fuzz -i /test/inputs -o /test/output -D -- "$BLD"/afl_test @@

#"$BLD"/afl_test /test/inputs/1.caff