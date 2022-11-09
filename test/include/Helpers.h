
//
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 11. 09.
//


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

#ifndef SHOPPINGLIKEFILES_NATIVECOMPONENT_HELPERS_H
#define SHOPPINGLIKEFILES_NATIVECOMPONENT_HELPERS_H

#include <cstdint>
#include <vector>
#include <cstring>

namespace CREDITS {
    const int YEAR_OFFSET = 0;
    const int MONTH_OFFSET = 2;
    const int DAY_OFFSET = 3;
    const int HOUR_OFFSET = 4;
    const int MINUTE_OFFSET = 5;
    const int CREATOR_LEN_OFFSET = 6;
    const int CREATOR_OFFSET = 14;
}

namespace HEADER {
    const int MAGIC_OFFSET = 0;
    const int LEN_OFFSET = 4;
    const int ANIM_OFFSET = 12;
}

template<typename T>
std::vector<uint8_t> ConvertToArray(T data) {
    std::size_t size = sizeof(T) / sizeof(uint8_t);

    uint8_t a[size];

    memcpy(a, &data, size * sizeof(uint8_t));

    std::vector<uint8_t> vec(a, a + size);

    return vec;
}

std::vector<uint8_t> GetValidCredit() {
    std::vector<uint8_t> vec;
    uint16_t year = 2020;

    auto y = ConvertToArray(year);

    vec.insert(vec.end(), y.begin(), y.end());
    vec.push_back(1); //month
    vec.push_back(2); //day
    vec.push_back(3); //h
    vec.push_back(4); //m
    std::string creator = "Test Creator";
    uint64_t creatorlen = creator.length();
    auto c = ConvertToArray(creatorlen);
    vec.insert(vec.end(), c.begin(), c.end());
    vec.insert(vec.end(), creator.begin(), creator.end());
    vec.shrink_to_fit();

    return vec;
}

std::vector<uint8_t> GetValidHeader(uint64_t num_anim) {
    std::vector<uint8_t> vec;

    std::string caff = "CAFF";
    vec.insert(vec.end(), caff.begin(), caff.end());

    uint64_t header_size = 20;
    auto hs = ConvertToArray(header_size);
    auto na = ConvertToArray(num_anim);

    vec.insert(vec.end(), hs.begin(), hs.end());
    vec.insert(vec.end(), na.begin(), na.end());

    vec.shrink_to_fit();

    return vec;
}

#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_HELPERS_H
