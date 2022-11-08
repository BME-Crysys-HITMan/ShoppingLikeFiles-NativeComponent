
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
#include <set>

#define YEAR_OFFSET 0
#define MONTH_OFFSET 2
#define DAY_OFFSET 3
#define HOUR_OFFSET 4
#define MINUTE_OFFSET 5
#define CREATOR_LENGTH_OFFSET 6
#define CREATOR_OFFSET 14

class fileEndReached : public std::exception {
public:
    const char *what() const noexcept override {
        return "File end reached";
    }
};

BasicBlock GetBlock(std::ifstream &stream) {
    char id;
    NativeComponent::Types::INT64 size;
    if (!(stream >> id)) {
        std::cout << "End reached!" << std::endl;
        throw fileEndReached();
    }

    stream.read((char *) &size, 8);
    char content[size.getValue()];
    stream.read(content, size.getValue());
    /**
     * Maybe size.getValue() converted to signed could be negative.
     */
    BasicBlock block{
            CAFF::Utils::getBlockType(id),
            size
    };

    block.setData((uint8_t *) content);

    return block;
}

namespace CAFF {
    CAFFProcessor::~CAFFProcessor() {
        //delete[] fileName;
    }

    CAFFProcessor::CAFFProcessor(const char *filename) {
        fileName = filename;
    }

    bool CAFFProcessor::ValidateFile() {
        std::ifstream fileStream;
        fileStream.open(this->fileName, std::ifstream::binary);

        if (!fileStream) {
            return false;
        }
        bool isValid;
        uint64_t numAnim;
        try {
            auto block = GetBlock(fileStream);

            isValid = ValidateHeader((uint8_t *) block.data, block.contentSize.getValue(), &numAnim);

            if (!isValid)
                return isValid;

            while (fileStream.good()) {
                auto block = GetBlock(fileStream);

                switch (block.blockType) {
                    case Utils::Credits:
                        isValid = ValidateCredits((uint8_t *) block.data, block.contentSize.getValue());
                        break;
                    case Utils::Animation:
                        if (numAnim == 0)
                            return false;

                        isValid = ValidateAnimation((uint8_t *) block.data, block.contentSize.getValue());
                        --numAnim;
                        break;
                    default:
                        if (numAnim == 0 && isValid) {
                            return true;
                        }
                        return false;
                }

                if (!isValid)
                    return isValid;
            }
            return isValid;
        }
        catch (fileEndReached &ex) {
            if (isValid && numAnim == 0) {
                return true;
            }
            std::cerr << ex.what() << std::endl;
            return false;
        }
        catch (std::exception &ex) {
            std::cerr << ex.what() << std::endl;
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

                this->metadata.height = header->height;
                this->metadata.width = header->width;

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

    void CAFFProcessor::ProcessCredit(uint8_t *data) {
        int creator_lenSize = 8;
        int64_t creator_len;
        GetData(data, CREATOR_LENGTH_OFFSET, creator_lenSize, &creator_len);

        char creator[creator_len + 1];
        GetData(data, CREATOR_OFFSET, creator_len, creator);

        creator[creator_len] = '\0';
        this->metadata.creator = std::string(creator);
    }

    void CAFFProcessor::ProcessTags(uint8_t *data) {

    }


}

