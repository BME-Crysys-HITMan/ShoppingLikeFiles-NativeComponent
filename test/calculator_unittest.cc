//
// Created by Daniel on 2022. 10. 18..
//
#include <gtest/gtest.h>
#include "../src/calculator.h"

TEST(asd, asd){
    int a = 6;
    int b = 7;
    EXPECT_EQ(a+b, Add(a, b));
}