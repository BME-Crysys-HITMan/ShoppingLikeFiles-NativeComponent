cmake_minimum_required(VERSION 3.22)

project(ShoppingLikeFiles_NativeComponent)

set(CMAKE_CXX_STANDARD 17)

option(ci-run "Running tests in CI environment." OFF)

if (ci-run)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping -mllvm -runtime-counter-relocation -O0 -g")
endif ()

message("Compiler: ${CMAKE_CXX_COMPILER}")
message("Flags: ${CMAKE_CXX_FLAGS}")

add_executable(CAFF_Processor
        src/CAFF_Processor.cc
        src/CAFF_validation.cc
        src/CIFF_validation.cc
        src/Util.cc src/main.cc src/CIFF_Processor.cc src/BasicBlock.cc src/CIFF_Utils.cc include/CIFF_Utils.h)

target_include_directories(CAFF_Processor PRIVATE include)

enable_testing()
add_subdirectory(test)



