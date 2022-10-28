
//
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 10. 28.
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

#ifndef SHOPPINGLIKEFLIES_AFL_CAFF_VALIDATION_H
#define SHOPPINGLIKEFLIES_AFL_CAFF_VALIDATION_H

#include "Utils.h"

/**
 * Validates a CAFF header block
 * @param data field of containing block
 * @return true, if header is valid
 */
bool ValidateHeader(uint8_t *data, size_t length);

/**
 * Validates a CAFF Credits block
 * @param data field of containing block
 * @return true, it credits are valid
 */
bool ValidateCredits(uint8_t *data, size_t length);

/**
 * Validates a CAFF animation block
 * @param data field of containing block
 * @return true if duration and containing CIFF is valid
 */
bool ValidateAnimation(uint8_t *data, size_t length);

#endif //SHOPPINGLIKEFLIES_AFL_CAFF_VALIDATION_H
