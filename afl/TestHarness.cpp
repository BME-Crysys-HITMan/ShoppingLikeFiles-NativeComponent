
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
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 10. 27.
//

#include <iostream>
#include <string>
#include <fstream>
#include "CAFF_Processor.h"

namespace Type = NativeComponent::Types;

void printArgs(int argc, char **argv) {
    std::ofstream fout;
    fout.open("arguments.txt");

    if (fout.fail()) {
        abort();
    }

    fout << "Number of arguments: " << argc << std::endl;

    for (auto i = 0; i < argc; ++i) {
        fout << "Argument " << i << " is " << argv[i] << std::endl;
    }

    fout.flush();
    fout.close();
}

int main(int argc, char **argv) {
    //printArgs(argc, argv);

    if (argc < 2) {
        std::cout << "Usage: application /path/to/file" << std::endl;
        exit(-1);
    }

    CAFF::CAFFProcessor processor(argv[1]);
    auto isValid = processor.ValidateFile();
    CIFF::Pixel *pixels = nullptr;
    pixels = processor.GenerateThumbnailImage();

    if (pixels != nullptr)
        delete[] pixels;

    return 0;
}