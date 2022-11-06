
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
#include <fstream>
#include "Utils.h"
#include "CAFF_validation.h"
#include "BasicBlock.h"

BasicBlock GetBlock(std::ifstream &stream) {
    unsigned char id;
    NativeComponent::Types::INT64 size;

    stream >> id;
    stream >> size;
    char c;
    stream >> c;
    char content[size.getValue()];

    auto siz = stream.readsome(&content[0], size.getValue());
    /**
     * Maybe size.getValue() converted to signed could be negative.
     */
    if (siz == size.getValue()) {
        BasicBlock block{
                CAFF::Utils::getBlockType(id),
                size
        };

        block.setData((unsigned char *) content);

        return block;
    }

    throw std::exception();
}

namespace CAFF {
    CAFFProcessor::CAFFProcessor() {
        fileName = nullptr;
        header = Header();
        metadata = Credit();
    }

    CAFFProcessor::~CAFFProcessor() {
        delete[] fileName;
    }

    CAFFProcessor::CAFFProcessor(const char *filename) : CAFFProcessor() {
        fileName = filename;
    }

    bool CAFFProcessor::ValidateFile() {
        std::ifstream fileStream;
        fileStream.open(this->fileName, std::ifstream::binary);

        if (!fileStream) {
            return false;
        }

        try {
            bool isValid;

            auto block = GetBlock(fileStream);
            /*std::cout << "DEBUG" << std::endl;
            for (std::size_t i = 0; i < block.contentSize.getValue(); ++i) {
                std::cout << (int) *block.data++ << std::endl;
            }*/
            uint64_t numAnim;
            isValid = ValidateHeader(block.data, block.contentSize.getValue(), &numAnim);

            if (!isValid)
                return isValid;

            while (!fileStream) {
                block = GetBlock(fileStream);

                switch (block.blockType) {
                    case Utils::Credits:
                        isValid = ValidateCredits(block.data, block.contentSize.getValue());
                        break;
                    case Utils::Animation:
                        if (numAnim == 0)
                            return false;

                        isValid = ValidateAnimation(block.data, block.contentSize.getValue());
                        --numAnim;
                        break;
                    default:
                        return false;
                }

                if (!isValid)
                    return isValid;
            }
            return isValid;
        }
        catch (std::exception &ex) {
            return false;
        }
    }

    CIFF::Pixel *CAFFProcessor::GenerateThumbnailImage() {
        CIFF::Pixel *pixels = nullptr;
        bool hasCiff = false;

        std::ifstream file;
        file.open(this->fileName);

        while (!hasCiff) {
            auto block = GetBlock(file);
            if (block.blockType == Utils::Animation) {
                hasCiff = true;
                CIFF::CIFFProcessor proc;

                auto header = proc.ProcessHeader(block.data);
                pixels = proc.GetImage(block.data, header);

                /**
                 * Could find non-0 length contentSize...
                 */
            }
        }

        return pixels;
    }

    Credit CAFFProcessor::GetCredits() {
        return this->metadata;
    }


}

