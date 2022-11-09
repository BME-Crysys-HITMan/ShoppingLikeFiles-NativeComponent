//
// Created by kerek on 2022. 11. 09..
//

#include "CIFF_Utils.h"

std::string getCaption(uint8_t *data, std::size_t start, std::size_t header_size) {
    std::vector<char> vec;
    uint8_t *p = data + start;
    size_t counter = 0;
    while (counter < header_size) {
        ++counter;
        auto c = (char) *p++;
        vec.push_back(c);
        if(c == '\n')
            break;
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
    int length = 0;
    char c;
    uint8_t *ptr = data + start;
    for (int i = 0; i < len; ++i) {
        c = (char) *ptr;
        array[length] = c;
        length++;
        if (c == '\0') {
            ret.emplace_back(std::string(array, length-1));
            length = 0;
            array[0] = '\0';
        }
        ++ptr;
    }
    return ret;
}
