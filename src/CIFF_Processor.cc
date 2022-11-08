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
#include "CIFF_Processor.h"
#include "CIFF_validation.h"

#define DURATION_LENGTH 8;

#define MAGIC_OFFSET 0
#define HEADER_SIZE_OFFSET 4
#define CONTENT_SIZE_OFFSET 12
#define WIDTH_OFFSET 20
#define HEIGHT_OFFSET 28
#define CAPTION_OFFSET 36

std::string getCaption(uint8_t *data, std::size_t start) {
    std::vector<char> vec;
    uint8_t *p = data + start;
    while (*p != '\n') {
        auto c = (char) *p++;
        vec.push_back(c);
    }
    vec.push_back('\0');
    vec.shrink_to_fit();
    std::string s(vec.data());
    return s;
}

size_t getTagsLength(size_t headerSize, std::size_t captionLength) {
    size_t magicLength = 4;
    size_t headerConstantLength = 32;
    return headerSize - magicLength - headerConstantLength - captionLength;
}

std::vector<std::string> getTags(uint8_t *data, uint64_t start, uint64_t len) {
    std::vector<std::string> ret;
    char array[len];
    uint8_t *ptr = data + start;
    for (int i = 0; i < len; ++i) {

    }
}


CIFF::Header *CIFF::CIFFProcessor::ProcessHeader(uint8_t *data) {
    Header *header = new Header();

    GetData(data, HEADER_SIZE_OFFSET, 8, &header->headerSize);
    GetData(data, CONTENT_SIZE_OFFSET, 8, &header->contentSize);
    GetData(data, HEADER_SIZE_OFFSET, 8, &header->width);
    GetData(data, HEADER_SIZE_OFFSET, 8, &header->height);
    header->caption = getCaption(data, CAPTION_OFFSET);


    return header;
}

CIFF::Pixel *CIFF::CIFFProcessor::GetImage(uint8_t *data, CIFF::Header *header) {
    return nullptr;
}

bool CIFF::CIFFProcessor::IsValid(uint8_t *data, NativeComponent::Types::INT64 ciffSize) {
    bool isValid = validateHeader(data);
    if (!isValid)
        return isValid;

    auto length = ciffSize.getValue() - DURATION_LENGTH;

    isValid = validateContent(data, length);

    return isValid;
}
