
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
        fileStream.seekg(0, std::ifstream::end);
        fileSize = fileStream.tellg();
        fileStream.seekg(0, std::ifstream::beg);
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

            /**
             * Changes for klee
             */
            std::vector<char> input;
            for (std::size_t i = 0; i < length; ++i) {
                char c;
                fileStream.get(c);
                input.push_back(c);
            }

            input.shrink_to_fit();

            auto block = std::make_shared<BasicBlock>();

            block->blockType = Utils::getBlockType(id);
            block->contentSize = NativeComponent::Types::INT64(input.size());
            block->setData(input.data());

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
                return this->isValidFile;
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
            auto id = static_cast<unsigned char>(ID);
            ifs.read((char *) &length, 8);
            std::vector<unsigned char> input;
            for (std::size_t i = 0; i < length; ++i) {
                char c;
                ifs.get(c);
                auto p = static_cast<unsigned char>(c);
                input.push_back(p);
            }
            input.shrink_to_fit();
            auto block = std::make_shared<BasicBlock>();

            block->blockType = Utils::getBlockType(id);
            if (block->blockType == Utils::Animation) {
                const unsigned long long durationSize = 8;
                NativeComponent::Types::INT64 ciffSize(length);
                std::vector<uint8_t> ciff(input.begin() + durationSize, input.end());

                std::unique_ptr<CIFF::Header> header(CIFF::CIFFProcessor::ProcessHeader(ciff.data()));

                this->metadata.height = header->height;
                this->metadata.width = header->width;

                pixels = CIFF::CIFFProcessor::GetImage(ciff.data(), header.get());

                return pixels;
                /**
                 * Could find non-0 length contentSize...
                 */
            }
        }

        return pixels;
    }

    Credit CAFFProcessor::GetCredits() const {
        return this->metadata;
    }

    void CAFFProcessor::ProcessCredit(const uint8_t *data) {
        int creator_lenSize = 8;
        int64_t creator_len;
        GetData(data, CREATOR_LENGTH_OFFSET, creator_lenSize, &creator_len);
        std::vector<char> creator(creator_len + 1);
        GetData(data, CREATOR_OFFSET, creator_len, creator.data());

        creator[creator_len] = '\0';

        GetData(data, YEAR_OFFSET, 2, &this->metadata.year);
        GetData(data, MONTH_OFFSET, 1, &this->metadata.month);
        GetData(data, DAY_OFFSET, 1, &this->metadata.day);
        GetData(data, HOUR_OFFSET, 1, &this->metadata.hour);
        GetData(data, MINUTE_OFFSET, 1, &this->metadata.minute);

        this->metadata.creator = std::string(creator.data());
    }

    void CAFFProcessor::ProcessTags(const uint8_t *data) {
        auto header = std::unique_ptr<CIFF::Header>(CIFF::CIFFProcessor::ProcessHeader(data + ANIMATION_CIFF_OFFSET));

        this->tags.insert(header->tags.begin(), header->tags.end());
    }

    std::set<std::string, std::less<>> CAFFProcessor::GetTags() const {
        return this->tags;
    }
}

