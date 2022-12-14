
//
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 10. 20.
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

#ifndef SHOPPINGLIKEFILES_NATIVECOMPONENT_UTILS_H
#define SHOPPINGLIKEFILES_NATIVECOMPONENT_UTILS_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <cstring>
#include <memory>

namespace CAFF::Utils {
    enum CAFF_Block_Type {
        Header,
        Credits,
        Animation,
        Unknown
    };

    /**
     *
     * @param id section of a block
     * @return Returns a block type.
     *
     * @exception
     * Throws std::exception() if id type is unknown
     */
    CAFF_Block_Type getBlockType(uint8_t id);
}

namespace NativeComponent::Types {
    template<typename T>
    class TypeBase {

    public:
        T getValue();

    protected:
        T value;

        void Set(T data);
    };

    class INT64 : public TypeBase<unsigned long long> {
    public:
        INT64();

        INT64(unsigned long long initial);

        INT64(char arr[]);

        unsigned long long getValue();

        void FromArray(std::vector<char> vec);

    protected:
        void setValue(char *arr, std::size_t len);
    };
}

template<typename T>
void GetData(const unsigned char *data, unsigned long long start, unsigned long long length, T *result) {
    mempcpy((char *) result, &data[start], length);
}

#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_UTILS_H
