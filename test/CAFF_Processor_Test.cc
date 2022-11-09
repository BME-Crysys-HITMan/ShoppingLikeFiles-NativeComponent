
// MIT License
//
// Copyright (c) 2022.  - BME-Crysys-HITMan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


//
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 11. 09.
//
#include <gtest/gtest.h>
#include "CAFF_Processor.h"

#if defined(__linux__)
const std::string folder = "/home/runner/work/ShoppingLikeFiles-NativeComponent/ShoppingLikeFiles-NativeComponent/afl/testfiles/";
#elif defined(_WIN64) || defined(_WIN32)
const std::string folder = "../../afl/testfiles/";
#endif

TEST(CAFF_Processor, ValidTest1) {
    std::cout << "Running with folder: " << folder << std::endl;
    std::string file = folder + "1.caff";
    CAFF::CAFFProcessor proc(file.c_str());
    EXPECT_TRUE(proc.ValidateFile());
}

TEST(CAFF_Processor, ValidTest2) {
    std::string file = folder + "2.caff";
    CAFF::CAFFProcessor proc(file.c_str());
    EXPECT_TRUE(proc.ValidateFile());
}

TEST(CAFF_Processor, ValidTest3) {
    std::string file = folder + "3.caff";
    CAFF::CAFFProcessor proc(file.c_str());
    EXPECT_TRUE(proc.ValidateFile());
}