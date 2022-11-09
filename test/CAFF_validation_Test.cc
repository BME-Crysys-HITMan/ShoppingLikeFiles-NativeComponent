
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
#include "CAFF_validation.h"
#include "include/Helpers.h"

/**
 * Testcase: Valid header, based on specification
 * <br>
 * Expected:
 * <br>
 * Returns true (valid)<br>
 * num_anim is correctly returned
 */
TEST(CAFF_Validation, AssertHeader_Valid1) {
    //Arrange
    uint64_t expectedNumAnim = 2;
    auto vec = GetValidHeader(expectedNumAnim);
    uint64_t numAnim;

    //Act
    bool valid = ValidateHeader(vec.data(), vec.size(), &numAnim);

    //Assert
    EXPECT_TRUE(valid);
    EXPECT_EQ(expectedNumAnim, numAnim);
}

/**
 * Testcase: Actual data is smaller that, that is specified as header_size
 */
TEST(CAFF_Validation, AssertHeader_Invalid1) {
    //Arrange
    uint64_t expectedNumAnim = 2;
    auto vec = GetValidHeader(expectedNumAnim);
    uint64_t numAnim;
    vec.at(10) = 15;

    bool valid = ValidateHeader(vec.data(), vec.size(), &numAnim);
    EXPECT_FALSE(valid);
}

/**
 * Testcase: Length of actual data is larger that, that is specified in header
 */
TEST(CAFF_Validation, AssertHeader_Invalid2) {
    uint8_t data[] = {
            'C', 'A', 'F', 'F',                            // magic
            20, 0, 3, 0, 0, 0, 0, 0,    // header_size
            2, 0, 0, 0, 0, 0, 0, 0,      // num_anim
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0,
    };

    uint64_t numAnim;
    bool valid = ValidateHeader(data, 33, &numAnim);
    EXPECT_FALSE(valid);
}

/**
 * Testcase: Magic is incorrect
 */
TEST(CAFF_Validation, AssertHeader_InvalidMagic) {
    uint8_t data[] = {
            'C', 'O', 'C', 'K',                            // magic
            20, 0, 0, 0, 0, 0, 0, 0,    // header_size
            2, 0, 0, 0, 0, 0, 0, 0,      // num_anim
    };

    uint64_t numAnim;
    bool valid = ValidateHeader(data, 20, &numAnim);
    EXPECT_FALSE(valid);
}

/**
* Testcase: Valid credits block
*/
TEST(CAFF_Validation, AssertCredits_Valid) {
    auto vec = GetValidCredit();

    bool valid = ValidateCredits(vec.data(), vec.size());

    ASSERT_TRUE(valid);
}

/**
* Testcase: Invalid credits
*/
TEST(CAFF_Validation, AssertCredits_Invalid) {
    auto vec = GetValidCredit();
    vec.at(7) = 45;

    bool valid = ValidateCredits(vec.data(), vec.size());

    ASSERT_FALSE(valid);
}

