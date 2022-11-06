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


CIFF::Header *CIFF::CIFFProcessor::ProcessHeader(uint8_t *data) {
    return nullptr;
}

CIFF::Pixel *CIFF::CIFFProcessor::GetImage(uint8_t *data, CIFF::Header *header) {
    return nullptr;
}

bool CIFF::CIFFProcessor::IsValid(uint8_t *data, NativeComponent::Types::INT64 ciffSize) {
    bool isValid = validateHeader(data);
    if(!isValid)
        return isValid;

    isValid = validateContent(data, ciffSize.getValue());

    return isValid;
}
