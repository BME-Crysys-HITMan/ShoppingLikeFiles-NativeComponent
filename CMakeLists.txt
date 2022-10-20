cmake_minimum_required(VERSION 3.22)

project(ShoppingLikeFiles_NativeComponent)

set(CMAKE_CXX_STANDARD 20)

option(ci-run "Running tests in CI environment." OFF)

if (ci-run)
    if (DEFINED ENV{LLVM_PATH})
        set(clangRoute "$ENV{LLVM_PATH}/bin/clang++" CACHE INTERNAL "Copied from environment variable")
        message("Clang path = ${clangRoute}")
        set(CMAKE_CXX_COMPILER "${clangRoute}")
    else ()
        set(CMAKE_CXX_COMPILER clang++)
    endif ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping -mllvm -runtime-counter-relocation -O0 -g")
endif ()

message("Compiler: ${CMAKE_CXX_COMPILER}")
message("Flags: ${CMAKE_CXX_FLAGS}")

add_library(ShoppingLikeFiles_NativeComponent SHARED src/library.cpp src/calculator.cc src/calculator.h)

enable_testing()
add_subdirectory(test)



