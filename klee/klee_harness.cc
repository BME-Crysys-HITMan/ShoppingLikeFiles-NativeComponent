
//
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 11. 16.
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

#include <CAFF_validation.h>
#include <CAFF_Processor.h>

const int SIZE = 20;

int main(int argc, char **argv) {

    if (argc < 2) {
        return 1;
    }
    /*uint8_t data[SIZE];
    memcpy(data, argv[1], SIZE * sizeof(uint8_t));*/

    CAFF::CAFFProcessor proc(argv[1]);

    uint64_t numAnim;

    bool res = proc.ValidateFile();

    if (res) {
        std::cout << "File is valid!" << std::endl;
        return 0;
    }
    return 1;
}