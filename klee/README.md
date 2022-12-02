inside klee docker container

## init environment

```bash
export LLVM_COMPILER=clang
export LLVM_COMPILER_PATH=/usr/lib/llvm-11/bin
export LIBCXX_LIB=/tmp/libc++-install-110/lib/
export LIBCXX_ABI_LIB=/tmp/libc++-install-110/lib/
export LIBCXX_INC_DIR=/tmp/libc++-install-110/include/c++/v1/

export CXX_FLAGS="-nostdinc++ -stdlib=libc++ -lc++ -lc++abi -I$LIBCXX_INC_DIR -L$LIBCXX_LIB"
```

## make project

```bash
mkdir build | cd build

CC=wllvm CXX=wllvm++ cmake -DCMAKE_CXX_FLAGS="$CXX_FLAGS" ..

make

extract-bc klee_harness
```

## run klee

```shell
klee --libcxx --libc=uclibc --posix-runtime kleeCredit.bc -sym-arg 20
```