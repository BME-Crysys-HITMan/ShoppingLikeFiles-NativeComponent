
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

#include <sstream>
#include "CIFF_validation.h"

/**
 * Pixel values in RGB.
 */
#define NUMBER_OF_PIXELS = 3;

bool validateHeader(uint8_t *data) {
    return false;
}

bool validateContent(uint8_t *data, size_t content_size) {
    return false;
}

/**
 * This method validates a CIFF magic string.
 *
 * @param magic 4 bytes of char
 * @return Returns true if magic is 'CIFF', otherwise return false
 */
bool validateMagicString(unsigned char *magic) {
    return true;
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
    return true;
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
bool validateTags(char *tags, size_t length) {

}

/**
 * Finds the size of the caption field based on the following requirement:
 *
 * 1) Variable length ASCII encoded string ending with '\\n'.
 * 2) As '\\n' is a special character for the file format, the caption cannot contain this character.
 *
 * @param caption
 * @return
 */
size_t getCaptionLength(uint8_t *caption) {
    return 0;
}

/**
 *
 * Calculates the length of tags field based on the following specification:\n\n
 *
 * 1) Header size is the size of the header (all fields included)\n
 * 2) Size constants make up 4*8 bytes => 32 bytes (256 bits)\n
 * 3) Magic string make up 4 bytes (32 bits)\n
 * 4) Caption is variable length ASCII string\n
 * 5) The rest is made up of tags field
 *
 * @param headerSize Size of the header block.
 * @param captionSize Length of caption field.
 * @return Size of tags field.
 */
size_t getTagsLength(size_t headerSize, size_t captionSize) {
    return 0;
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
bool validateHeaderSize(size_t headerSize, size_t captionLength, size_t tagsLength) {
    return false;
}