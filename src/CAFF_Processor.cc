
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

#include <cstring>
#include <CAFF_Processor.h>
#include <iostream>
#include <random>
#include <chrono>
#include "Utils.h"

namespace CAFF {
    CAFFProcessor::CAFFProcessor() {
        isLittleEndian = NativeComponent::Utils::isLittleEndian();
        fileName = nullptr;
        header = Header();
        metadata = Credit();
    }

    CAFFProcessor::~CAFFProcessor() {
        delete fileName;
    }

    CAFFProcessor::CAFFProcessor(const char *filename) : CAFFProcessor() {
        fileName = new char[strlen(filename)];
        memcpy(fileName, filename, strlen(filename));
    }

    bool CAFFProcessor::ValidateFile() {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);

        auto n = generator() % 100;

        if (n < 5) {
            abort();
        }
        std::cout << n;
        return true;
    }

    CIFF::Pixel *CAFFProcessor::GenerateThumbnailImage() {
        auto *pixels = new CIFF::Pixel[15];

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);

        auto n = generator() % 100;

        if (n < 5) {
            abort();
        }

        return pixels;
    }
}

