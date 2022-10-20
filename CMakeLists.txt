cmake_minimum_required(VERSION 3.22)

project(ShoppingLikeFiles_NativeComponent)

set(CMAKE_CXX_STANDARD 20)

option(ci-run "Running tests in CI environment." OFF)

if(ci-run)
    set(CMAKE_CXX_COMPILER "clang++")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping -O0 -g")
endif()

add_library(ShoppingLikeFiles_NativeComponent SHARED src/library.cpp src/calculator.cc src/calculator.h)

enable_testing()
add_subdirectory(test)



