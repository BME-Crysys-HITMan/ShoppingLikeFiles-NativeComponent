// MIT License
//
// Copyright (c) 2022 BME-Crysys-HITMan
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
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 11/6/2022.
//

#include "CAFF_Processor.h"
#include <string>
#include <iostream>
#include <memory>
#include <fstream>

int main(int argv, char **argc) {
    if (argv < 3) {
        std::cout << "Usage: CAFF_Processor /path/to/file [options]" << std::endl;
        if (argv == 2) {
            std::string fileName(argc[1]);
            if (fileName == "--help") {
                std::cout << "Usage: CAFF_Processor /path/to/file [options]" << std::endl;
                std::cout << "Commands:" << std::endl;
                std::cout << "--validate\tValidates a file. Prints 1 if file is valid." << std::endl;
                std::cout
                        << "--getThumbnail\tGenerated a thumbnail image and puts it to standard output. The sequence start with WidthHeightPixelData"
                        << std::endl;
                return 0;
            }
        }
        return 0;
    }

    std::string fileName(argc[1]);
    std::string command(argc[2]);

    CAFF::CAFFProcessor proc(fileName.c_str());

    if (command == "--validate") {
        auto isValid = proc.ValidateFile();
        std::cout << isValid << std::endl;
    } else if (command == "--getThumbnail") {
        if (argv < 4) {
            std::cout << "Usage: CAFF_Processor /path/to/file --getThumbnail /path/to/return/folder" << std::endl;
            return 0;
        }
        std::string folder(argc[3]);
        CIFF::Pixel *c = proc.GenerateThumbnailImage();

        auto credit = proc.GetCredits();
        uint64_t size = credit.width * credit.height;

        std::cout << credit.width << credit.height;

        auto index = fileName.find_last_of('/');
        auto f = fileName.substr(index);

        folder.append(f);
        folder.append(".pixels");
        std::ofstream ofs;

        try {
            ofs.open(folder, std::ios::binary);
            if (ofs.fail()) throw ("Can't open output file");
            ofs << credit.width << credit.height;

            for (std::size_t i = 0; i < size; ++i) {
                auto pixel = *c++;
                ofs << pixel.red << pixel.green << pixel.blue;
            }
        } catch (const char *err) {
            std::cerr << err;
        }

        //delete[] c;
    }

    return 0;
}