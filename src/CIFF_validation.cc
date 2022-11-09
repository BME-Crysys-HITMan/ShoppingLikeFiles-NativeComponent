
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
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 10. 28.
//

#include "CIFF_validation.h"

/**
 * Pixel values in RGB.
 */
#define NUMBER_OF_PIXELS 3;

/**
 * This method validates a CIFF magic string.
 *
 * @param magic 4 bytes of char
 * @return Returns true if magic is 'CIFF', otherwise return false
 */
bool validateMagicString(uint8_t *&magic) {
    char mc[5];
    for (int i = 0; i < 4; ++i) {
        mc[i] = (char) *magic++;
    }
    mc[4] = '\0';
    std::string s(mc);
    return s == "CIFF";
}

/**
 *
 * Validates the content size based on the following requirement:
 *
 * ContentSize must be width * height * 3
 *
 * @param contentSize Content size of the dataframe.
 * @param width Width of the image.
 * @param height Height of the image.
 * @return Returns true if contentSize is valid.
 */
bool validateContentSize(uint64_t contentSize, uint64_t width, uint64_t height) {
    return contentSize == width * height * NUMBER_OF_PIXELS;
}

/**
 * Validates the tags field of a CIFF header block.\n\n
 *
 * The following requirements must be met:\n\n
 *
 * 1) Variable number of variable length ASCII encoded strings, each separated by '\0' character\n
 * 2) The strings themselves must not be multiline.\n
 * 3) There must be a '\0' character after the last tag.\n
 *
 * @param tags contents of the tags field
 * @param length length of the tags field
 * @return Returns true if requirements met for a well-formed tags field.
 */
bool validateTags(char *tags, std::size_t length) {
    std::string s(tags, length);
    if (std::count(s.begin(), s.end(), '\n') > 0)
        return false;
    return s.at(length - 1) == '\0';
}

/**
 *
 * Validates the headerSize based on a sum.
 *
 * @param headerSize
 * @param captionLength
 * @param tagsLength
 * @return true, if header size is acceptable.
 */
bool validateHeaderSize(std::size_t headerSize, std::size_t captionLength, std::size_t tagsLength) {
    size_t magicLength = 4;
    size_t headerConstantLength = 32;
    return headerSize == (magicLength + headerConstantLength + captionLength + tagsLength);
}

size_t getLong(uint8_t *data, size_t start, size_t len) {
    std::size_t dat;
    GetData(data, start, len, &dat);

    return dat;
}

bool validateContent(uint8_t *data, std::size_t content_size) {
    auto headerSize = getLong(data, 4, 8);
    auto cSize = getLong(data, 12, 8);
    return content_size == headerSize + cSize;
}

bool validateHeader(uint8_t *data) {
    if (!validateMagicString(data))
        return false;

    size_t header_size = getLong(data, 0, 8);
    size_t content_size = getLong(data, 8, 8);
    size_t width = getLong(data, 16, 8);
    size_t height = getLong(data, 24, 8);

    if (!validateContentSize(content_size, width, height))
        return false;
    auto maxCaptionSize= content_size > header_size ? content_size-header_size : header_size-content_size;
    auto caption = getCaption(data, 32, maxCaptionSize);
    if(caption.back()!='\n')
        return false;
    size_t captionLength = caption.length();

    size_t tagsLength = getTagsLength(header_size, captionLength);

    if (!validateHeaderSize(header_size, captionLength, tagsLength)) {
        return false;
    }

    if((width==0 || height==0) && content_size!=0)
        return false;

    if (tagsLength == 0)
        return true;

    std::size_t tagsStart = 32 + captionLength;

    uint8_t *start = data + tagsStart;
    char tags[tagsLength];
    for (int i = 0; i < tagsLength; ++i) {
        tags[i] = static_cast<char>(*start++);
    }

    return validateTags(tags, tagsLength);
}
