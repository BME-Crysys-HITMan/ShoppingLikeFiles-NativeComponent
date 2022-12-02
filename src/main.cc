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
                        << "--getThumbnail\tGenerated a thumbnail image and puts the filename to standard output. The sequence start with WidthHeightPixelData"
                        << std::endl;
                std::cout.flush();
                return 0;
            }
        }
        std::cout.flush();
        return 0;
    }

    std::string fileName(argc[1]);
    std::string command(argc[2]);

    CAFF::CAFFProcessor proc(fileName.c_str());

    if (command == "--validate") {
        auto isValid = proc.ValidateFile();
        std::cout << isValid << std::endl;

        if(!isValid){
            return 0;
        }

        auto credits = proc.GetCredits();

        std::cout << credits.year << ":" << (int) credits.month << ":"
                  << (int) credits.day << ":" << (int) credits.hour << ":"
                  << (int) credits.minute << std::endl;

        std::cout << credits.creator << std::endl;
        auto tags = proc.GetTags();

        std::for_each(tags.begin(), tags.end(), [&](const auto &item) {
            std::cout << item << ";";
        });
        std::cout << std::endl;
    } else if (command == "--getThumbnail") {
        if (argv < 4) {
            std::cout << "Usage: CAFF_Processor /path/to/file --getThumbnail /path/to/return/folder" << std::endl;
            std::cout.flush();
            return 0;
        }
        std::string folder(argc[3]);
        CIFF::Pixel const *pPixel = proc.GenerateThumbnailImage();

        auto credit = proc.GetCredits();
        uint64_t size = credit.width * credit.height;

        auto index = fileName.find_last_of('/');
        if (fileName.length() < index) {
            index = fileName.find_last_of('\\');
        }
        auto f = fileName.substr(index);

        folder.append(f);
        folder.append(".pixels");
        std::ofstream ofs;

        try {
            ofs.open(folder, std::ios::binary);
            if (ofs.fail()) throw "Can't open output file";

            ofs.write((char *) &credit.width, sizeof(uint64_t));
            ofs.write((char *) &credit.height, sizeof(uint64_t));

            for (std::size_t i = 0; i < size; ++i) {
                auto pixel = *pPixel++;
                ofs.write((char *) &pixel, sizeof(CIFF::Pixel));
            }

            ofs.flush();
            ofs.close();
            std::cout << folder << std::endl;
        } catch (const char *err) {
            std::cerr << err;
        }
    }
    std::cout.flush();
    return 0;
}