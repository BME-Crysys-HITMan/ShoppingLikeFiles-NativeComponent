cmake_minimum_required(VERSION 3.22)

project(ShoppingLikeFlies_AFL)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")


add_executable(
        afl_test
        TestHarness.cpp
        ../src/CAFF_Processor.cc
        ../include/Utils.h
        ../src/CIFF_Processor.cc
        ../src/Util.cc
        ../src/CIFF_validation.cc
        ../src/CAFF_validation.cc
        ../src/BasicBlock.cc)

target_include_directories(afl_test PRIVATE ../include)

target_link_libraries(afl_test)