#!/usr/bin/env bash


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

echo "Test file compactor utility for HITman team"
echo

if [ "$#" -lt "2" ]; then
  echo "Usage: $0 /path/to/test_files /path/to/src_dir [... target params...]"
  echo
  echo "Example run ./get_test_files.sh /test/output/default /code/afl/error_cases"
  echo
  exit 1
fi

SRC="$1"
DST="$2"
shift
shift

i=0

for entry in "$SRC"/crashes/*
do
  echo "$entry"
  # shellcheck disable=SC2016
  #echo cp "$entry" "$DST/crash_$i.caff"
  cp "$entry" "$DST/crash_$i.caff"
  let "i++"
done

i=1

for entry in "$SRC"/hangs/*
do
  echo "$entry"
  echo cp "$entry" "$DST/crash_$i.caff"
  cp "$entry" "$DST/hang_$i.caff"
  let "i++"
done

