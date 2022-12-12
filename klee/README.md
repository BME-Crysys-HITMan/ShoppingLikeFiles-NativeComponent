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

extract-bc SFL_Klee
```

## run klee

### First run
```shell
klee --only-output-states-covering-new --libcxx --libc=uclibc --posix-runtime --optimize \
 --max-solver-time=5min --search=random-state --search=nurs:md2u --max-time=10min \
 SFL_Klee.bc A -sym-files 1 120
```

#### Results

The run resulted in a ~51% overall code coverage including std libs.

### Long run
```shell
klee --only-output-states-covering-new --libcxx --libc=uclibc --posix-runtime --optimize \
--max-solver-time=5min --search=random-state --search=nurs:md2u --max-time=10min \
SFL_Klee.bc A -sym-files 1 120
```

### DFS search
```shell
klee --only-output-states-covering-new --libcxx --libc=uclibc --posix-runtime --optimize \
--max-solver-time=5min --search=dfs   --max-time=10min \
SFL_Klee.bc A -sym-files 1 120
```