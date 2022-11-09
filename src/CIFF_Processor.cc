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
#include "CIFF_Utils.h"

CIFF::Header *CIFF::CIFFProcessor::ProcessHeader(uint8_t *data) {
    auto header = new Header();
    GetData(data, HEADER_SIZE_OFFSET, 8, &header->headerSize);
    GetData(data, CONTENT_SIZE_OFFSET, 8, &header->contentSize);
    GetData(data, WIDTH_OFFSET, 8, &header->width);
    GetData(data, HEIGHT_OFFSET, 8, &header->height);
    header->caption = getCaption(data, CAPTION_OFFSET, abs(header->contentSize-header->headerSize));
    header->caption.pop_back(); //remove \n from the end;
    auto captionLen = header->caption.length() + 1;
    uint64_t tagsStart = CAPTION_OFFSET + captionLen;

    header->tags = getTags(data, tagsStart, getTagsLength(header->headerSize, captionLen));

    return header;
}

CIFF::Pixel *CIFF::CIFFProcessor::GetImage(uint8_t *data, CIFF::Header *header) {
    auto *result = new CIFF::Pixel[sizeof(CIFF::Pixel) * (header->contentSize / 3)];
    int offset = header->headerSize;
    for (int i = 0; i < header->contentSize; i += 3) {
        int index = i + offset;
        result[i / 3] = CIFF::Pixel{
                data[index],
                data[index + 1],
                data[index + 2]
        };
    }
    return result;
}


bool CIFF::CIFFProcessor::IsValid(uint8_t *data, NativeComponent::Types::INT64 ciffSize) {
    if (ciffSize.getValue() < 36) {
        return false;
    }
    bool isValid = validateHeader(data);
    if (!isValid)
        return isValid;

    auto contentLength = ciffSize.getValue() - DURATION_LENGTH;

    isValid = validateContent(data, contentLength);
    return isValid;
}
