
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

#define ANIMATION_DURATION_OFFSET 0
#define ANIMATION_CIFF_OFFSET 8

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
            this->isValidFile = false;
            return false;
        }

        /**
         * Bugfix for AFL run 2 based errors
         */
        uint64_t fileSize;
        fileStream.seekg(0, fileStream.end);
        fileSize = fileStream.tellg();
        fileStream.seekg(0, fileStream.beg);
        /**
         * End of bugfix
         */

        bool firstBlock = true;
        char ID;

        int64_t length;
        uint64_t num_anim;


        /**
         * Bugfix after RUN 3
         */
        uint64_t alreadyRed = 0;
        while (fileStream.good() && fileSize > alreadyRed) {
            /**
             * Bugfix end
             */
            fileStream.read(&ID, 1);
            auto id = static_cast<uint8_t>(ID);
            if (firstBlock) {
                if (ID != 1) {
                    this->isValidFile = false;
                    return false;
                } else
                    firstBlock = false;
            }
            fileStream.read((char *) &length, 8);

            /**
             * Bugfix for AFL run 2 based errors
             */
            if (fileSize - fileStream.tellg() < length) {
                this->isValidFile = false;
                return false;
            }
            /**
             * End bugfix
             */

            /**
             * Bugfix for Run 4
             */
            if (length < 1) {
                this->isValidFile = false;
                return false;
            }
            /**
             * End bugfix
             */

            //char data[length];
            auto data = std::make_unique<char[]>(length);

            fileStream.read(data.get(), length);

            auto block = std::make_shared<BasicBlock>(data.get(), length);

            //BasicBlock block(data.get());
            block->blockType = Utils::getBlockType(id);

            /**
             * Bugfix for RUN 3
             */
            alreadyRed = fileStream.tellg();
            /**
             * Bugfix end
             */


            bool valid = false;

            switch (block->blockType) {
                case Utils::Header:
                    valid = ValidateHeader(block->data.get(), length, &num_anim);
                    break;
                case Utils::Credits:
                    valid = ValidateCredits(block->data.get(), length);
                    break;
                case Utils::Animation:
                    if (num_anim == 0) {
                        valid = false;
                        break;
                    }
                    valid = ValidateAnimation(block->data.get(), length);
                    --num_anim;
                    break;
                case Utils::Unknown:
                    valid = false;
            }
            this->isValidFile = valid;

            if (!valid) {
                return valid;
            }

            if (block->blockType == Utils::Credits) {
                ProcessCredit(block->data.get());
            } else if (block->blockType == Utils::Animation) {
                ProcessTags(block->data.get());
            }
        }
        return true;
    }

    CIFF::Pixel *CAFFProcessor::GenerateThumbnailImage() {
        CIFF::Pixel *pixels = nullptr;

        if (!this->isValidFile) {
            return pixels;
        }

        std::ifstream ifs(this->fileName, std::ifstream::binary);

        char ID;
        int64_t length;
        while (ifs.good()) {
            ifs.read(&ID, 1);
            int id = (int) ID;
            ifs.read((char *) &length, 8);
            auto data = std::make_unique<char[]>(length);
            ifs.read(data.get(), length);
            auto block = std::make_shared<BasicBlock>(data.get(), length);

            block->blockType = Utils::getBlockType(id);

            if (block->blockType == Utils::Animation) {
                CIFF::CIFFProcessor proc;
                unsigned long long durationSize = 8;
                NativeComponent::Types::INT64 ciffSize(length);
                unsigned long long contentLength = ciffSize.getValue() - durationSize;
                auto *ciff = new uint8_t[sizeof(uint8_t) * contentLength];
                GetData(block->data.get(), durationSize, contentLength, ciff);
                std::unique_ptr<CIFF::Header> header(proc.ProcessHeader((uint8_t *) ciff));

                this->metadata.height = header->height;
                this->metadata.width = header->width;

                pixels = proc.GetImage((uint8_t *) ciff, header.get());

                delete[] ciff;

                return pixels;
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

        char *creator = new char[creator_len + 1];
        GetData(data, CREATOR_OFFSET, creator_len, creator);

        creator[creator_len] = '\0';

        this->metadata.creator = creator;
    }

    void CAFFProcessor::ProcessTags(uint8_t *data) {
        auto header = CIFF::CIFFProcessor::ProcessHeader(data + ANIMATION_CIFF_OFFSET);

        this->tags.insert(header->tags.begin(), header->tags.end());

        delete header;
    }


}

