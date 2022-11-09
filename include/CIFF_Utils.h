//
// Created by kerekesaron on 2022. 11. 09..
//

#ifndef SHOPPINGLIKEFILES_NATIVECOMPONENT_CIFF_UTILS_H
#define SHOPPINGLIKEFILES_NATIVECOMPONENT_CIFF_UTILS_H

#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_CIFF_UTILS_H
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>

#define DURATION_LENGTH 8

#define MAGIC_OFFSET 0
#define HEADER_SIZE_OFFSET 4
#define CONTENT_SIZE_OFFSET 12
#define WIDTH_OFFSET 20
#define HEIGHT_OFFSET 28
#define CAPTION_OFFSET 36

/**
 * Finds the size of the caption field based on the following requirement:
 *
 * 1) Variable length ASCII encoded string ending with '\\n'.
 * 2) As '\\n' is a special character for the file format, the caption cannot contain this character.
 *
 * @param caption
 * @return
 */
std::string getCaption(uint8_t *data, std::size_t start, std::size_t header_size);

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
 * @param captionLength Length of caption field.
 * @return Size of tags field.
 */
size_t getTagsLength(size_t headerSize, std::size_t captionLength);

std::vector<std::string> getTags(uint8_t *data, uint64_t start, uint64_t len);