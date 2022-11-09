
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
#include "Utils.h"
#include <set>

namespace CAFF {
    namespace Types = NativeComponent::Types;
    struct Credit {
        uint64_t width;
        uint64_t height;
        //Creator
        std::string creator;
    };

    class CAFFProcessor {
    private:
        const char *fileName;
        bool isValidFile = false;
        Credit metadata;
        std::set<std::string> tags;

        void ProcessCredit(uint8_t *data);

        void ProcessTags(uint8_t *data);

    public:
        explicit CAFFProcessor(const char *filename);

        ~CAFFProcessor();

        bool ValidateFile();

        CIFF::Pixel *GenerateThumbnailImage();

        Credit GetCredits();
    };
}


#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_CAFF_PROCESSOR_H
