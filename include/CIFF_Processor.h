
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

#ifndef SHOPPINGLIKEFILES_NATIVECOMPONENT_CIFF_PROCESSOR_H
#define SHOPPINGLIKEFILES_NATIVECOMPONENT_CIFF_PROCESSOR_H

#include <string>
#include "Utils.h"

namespace CIFF {
    struct Header {
        //Must be 4+8+8+8+8+len(caption)+len(tags)
        uint64_t headerSize;

        //It must be width * height * 3
        uint64_t contentSize;

        //Count be 0
        uint64_t width;

        //Could be 0
        uint64_t height;

        //Variable size ending with \n
        std::string caption;

        // Variable size each ending with \0
        std::vector<std::string> tags;
    };

    struct Pixel {
        //First
        uint8_t red;

        //Second
        uint8_t green;

        //Third
        uint8_t blue;
    };

    class CIFFProcessor {
    private:
    public:
        static Header *ProcessHeader(const uint8_t *data);

        static Pixel *GetImage(const uint8_t *data, Header *header);

        //CIFF_Validation.h
        static bool IsValid(const uint8_t *data, NativeComponent::Types::INT64 ciffSize);
    };
}

#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_CIFF_PROCESSOR_H
