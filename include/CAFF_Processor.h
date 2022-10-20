
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

#ifndef SHOPPINGLIKEFILES_NATIVECOMPONENT_CAFF_PROCESSOR_H
#define SHOPPINGLIKEFILES_NATIVECOMPONENT_CAFF_PROCESSOR_H

#include <string>
#include "CIFF_Processor.h"


namespace CAFF {
    struct Credit {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
    };

    struct Header {
        char *magicString;
        uint8_t headerSize;
        uint8_t numAnim;
    };

    class __declspec(dllexport) CAFFProcessor {
    private:
        char *fileName;
        bool isLittleEndian;
        Header header;
        Credit metadata;
    public:
        CAFFProcessor();

        CAFFProcessor(const char &filename);

        ~CAFFProcessor();

        bool ValidateFile();

        CIFF::Pixel *GenerateThumbnailImage();
    };
}


#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_CAFF_PROCESSOR_H
