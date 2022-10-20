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

add_library(TestLib ../src/library.cpp ../src/calculator.cc ../src/calculator.h)

add_executable(
        hello_test
        hello_test.cpp calculator_unittest.cc ../src/calculator.h)

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