//
// Created by Daniel on 2022. 10. 18..
//
#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions){

    EXPECT_STRNE("hello", "word");

    EXPECT_EQ(6*7, 42);
}