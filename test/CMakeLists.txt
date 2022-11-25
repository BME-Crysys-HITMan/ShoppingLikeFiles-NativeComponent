# @author Daniel Abraham

# Compile C++ test
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(TestLib
        ../src/CAFF_Processor.cc
        ../src/CIFF_Processor.cc
        ../src/CAFF_validation.cc
        ../src/CIFF_validation.cc
        ../src/BasicBlock.cc
        ../src/Util.cc
        ../src/CIFF_Utils.cc)

add_executable(
        hello_test
        Utils_unittest.cc
        ../src/CIFF_Processor.cc
        ../src/BasicBlock.cc 
        ../src/CIFF_Utils.cc 
        CIFF_Validation_Test.cc 
        CIFF_Processor_Test.cc 
        CIFF_Utils_unittest.cc
        ../src/CIFF_Processor.cc
        ../src/BasicBlock.cc 
        CAFF_validation_Test.cc 
        CAFF_Processor_Test.cc)


target_include_directories(hello_test PRIVATE ../include include)
target_include_directories(TestLib PRIVATE ../include)

target_link_libraries(
        hello_test
        TestLib
)

target_link_libraries(
        hello_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test
        XML_OUTPUT /testoutput)