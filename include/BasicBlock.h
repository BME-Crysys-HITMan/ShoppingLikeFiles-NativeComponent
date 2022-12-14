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
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 11/5/2022.
//

#ifndef SHOPPINGLIKEFILES_NATIVECOMPONENT_BASICBLOCK_H
#define SHOPPINGLIKEFILES_NATIVECOMPONENT_BASICBLOCK_H

#include "Utils.h"

struct BasicBlock {
    CAFF::Utils::CAFF_Block_Type blockType;
    NativeComponent::Types::INT64 contentSize;
    std::unique_ptr<unsigned char[]> data;

    void setData(const char *data);

    void setData(std::unique_ptr<unsigned char[]>);

    BasicBlock(std::unique_ptr<unsigned char[]> ptr);

    BasicBlock(std::unique_ptr<unsigned char[]> ptr, uint64_t size);

    BasicBlock(const char *data, uint64_t size);

    BasicBlock() : blockType(CAFF::Utils::Unknown), contentSize(), data(std::nullptr_t()) {};
};

#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_BASICBLOCK_H
