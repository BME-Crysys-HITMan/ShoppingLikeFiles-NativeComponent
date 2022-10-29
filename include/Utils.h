
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

namespace NativeComponent::Utils {
    bool isLittleEndian();
}

namespace CAFF::Utils {
    enum CAFF_Block_Type {
        Header,
        Credits,
        Animation
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

    class INT16 : TypeBase<unsigned short> {
    public:
        friend std::istream &operator>>(std::istream &input, INT16 &obj);

    protected:
        void setValue(unsigned char *arr, std::size_t len);
    };

    class INT64 : TypeBase<unsigned long long> {
    public:
        friend std::istream &operator>>(std::istream &input, INT64 &obj);

        friend std::ostream &operator<<(std::ostream &output, const INT64 &obj);

    protected:
        void setValue(unsigned char *arr, std::size_t len);
    };
}

#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_UTILS_H
