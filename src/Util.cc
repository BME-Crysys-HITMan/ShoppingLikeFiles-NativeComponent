
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
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 10. 20.
//
#include "Utils.h"
#include <bit>
#include <string>
#include <vector>
#include <cstring>

bool NativeComponent::Utils::isLittleEndian() {
    if constexpr (std::endian::native == std::endian::little) {
        return true;
    } else {
        return false;
    }
}

CAFF::Utils::CAFF_Block_Type CAFF::Utils::getBlockType(uint8_t id) {
    switch (id) {
        case 0x01: {
            return CAFF::Utils::CAFF_Block_Type::Header;
        }
        case 0x02: {
            return CAFF::Utils::CAFF_Block_Type::Credits;
        }
        case 0x03: {
            return CAFF::Utils::CAFF_Block_Type::Animation;
        }
        default: {
            return CAFF::Utils::CAFF_Block_Type::Unknown;
        }
    }
}

namespace Type = NativeComponent::Types;

template<typename T>
T Type::TypeBase<T>::getValue() {
    return value;
}

template<typename T>
void Type::TypeBase<T>::Set(T data) {
    value = data;
}


std::istream &NativeComponent::Types::operator>>(std::istream &input, NativeComponent::Types::INT16 &obj) {
    char arr[2];

    input >> arr;

    obj.setValue(arr, 2);

    return input;
}

void NativeComponent::Types::INT16::setValue(char *arr, std::size_t len) {
    if (len == 2) {
        char d[2] = {arr[0], arr[1]};
        auto data = std::bit_cast<uint16_t>(d);
        this->Set(data);
    }
}

void NativeComponent::Types::INT64::setValue(char *arr, std::size_t len) {
    bool little = Utils::isLittleEndian();
    if (len == 8) {
        char d[8];
        if (little) {
            for (std::size_t i = 0; i < len; ++i) {
                d[i] = arr[i];
            }
        } else {
            for (std::size_t i = 0; i < len; ++i) {
                d[i] = arr[7 - i];
            }
        }
        auto data = std::bit_cast<uint64_t>(d);
        this->Set(data);
    }
}

std::istream &NativeComponent::Types::operator>>(std::istream &input, NativeComponent::Types::INT64 &obj) {
    std::cout << "INT64 operator>>" << std::endl;
    char arr[8];

    input >> arr;

    std::cout << "array content:" << std::endl;

    auto print = [](const uint8_t &c) { std::cout << (int) (c) << std::endl; };

    std::for_each(&arr[0], &arr[7] + 1, print);

    obj.setValue(arr, 8);
    return input;
}

std::ostream &NativeComponent::Types::operator<<(std::ostream &output, const NativeComponent::Types::INT64 &obj) {
    output << obj.value;

    return output;
}

void NativeComponent::Types::INT64::FromArray(std::vector<char> vec) {
    this->setValue(vec.data(), vec.size());
}

unsigned long long NativeComponent::Types::INT64::getValue() {
    return TypeBase::getValue();
}

NativeComponent::Types::INT64::INT64() : TypeBase() {
    this->Set(0);
}

NativeComponent::Types::INT64::INT64(unsigned long long int initial) : TypeBase() {
    this->Set(initial);
}

NativeComponent::Types::INT64::INT64(char arr[]) : TypeBase() {
    uint64_t value;

    std::memcpy(&value, arr, sizeof(uint64_t));

    this->Set(value);
}
