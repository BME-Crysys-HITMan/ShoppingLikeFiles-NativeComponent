
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
#include "CAFF_validation.h"
#include "CIFF_Processor.h"
#include <cstring>
#include <string>
#include "Utils.h"


bool ValidateHeader_Magic(uint8_t *data, int end) {
    return std::string((char *) data, end) == "CAFF";
}

bool ValidateHeader_HeaderSize(uint8_t *data, int start, int headerSizeLength, std::size_t expectedHeaderSize) {
    int64_t header_size;
    GetData(data, start, headerSizeLength, &header_size);
    return expectedHeaderSize == header_size;
}

bool ValidateHeader(uint8_t *data, std::size_t length, uint64_t *num_anim) {
    int magicLength = 4;
    int headerSizeLength = 8;
    int numAnimLength = 8;
    if (length != magicLength + headerSizeLength + numAnimLength)
        return false;
    GetData(data, magicLength + headerSizeLength, numAnimLength, num_anim);

    return ValidateHeader_Magic(data, magicLength)
           && ValidateHeader_HeaderSize(data, magicLength, headerSizeLength, length);
}

bool ContainsOnlyASCII(char *string, int size) {
    for (int i = 0; i < size; i++) {
        if (static_cast<unsigned char>(string[i]) > 127) {
            return false;
        }
    }
    return true;
}

bool ValidateCredits(uint8_t *data, std::size_t length) {
    int start = 0;
    int yearSize = 2;
    int16_t year;
    GetData(data, start, yearSize, &year);
    start += yearSize;

    int monthSize = 1;
    int8_t month;
    GetData(data, start, monthSize, &month);
    start += monthSize;

    int daySize = 1;
    int8_t day;
    GetData(data, start, daySize, &day);
    start += daySize;

    int hourSize = 1;
    int8_t hour;
    GetData(data, start, hourSize, &hour);
    start += hourSize;

    int minuteSize = 1;
    int8_t minute;
    GetData(data, start, minuteSize, &minute);
    start += minuteSize;

    int creator_lenSize = 8;
    int64_t creator_len;
    GetData(data, start, creator_lenSize, &creator_len);
    start += creator_lenSize;

    if (length != start + creator_len)
        return false;

    char creator[creator_len];
    GetData(data, start, (int) creator_len, creator);

    return ContainsOnlyASCII(creator, creator_len);
}

bool ValidateAnimation(uint8_t *data, std::size_t length) {
    if (length < 8) {
        return false;
    }
    unsigned long long durationSize = 8;
    int64_t duration;
    GetData(data, 0, durationSize, &duration);

    NativeComponent::Types::INT64 ciffSize(length);

    unsigned long long contentLength = ciffSize.getValue() - durationSize;

    auto *ciff = new uint8_t[sizeof(uint8_t) * contentLength];
    GetData(data, durationSize, contentLength, ciff);
    CIFF::CIFFProcessor proc{};
    auto valid = proc.IsValid(ciff, ciffSize);
    delete[] ciff;
    return valid;
}
