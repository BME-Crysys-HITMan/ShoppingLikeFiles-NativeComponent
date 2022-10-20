
//
// Created by Daniel Abraham <daniel.abraham@edu.bme.hu> on 2022. 10. 20.
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

#ifndef SHOPPINGLIKEFILES_NATIVECOMPONENT_DLLPUBLICINTERFACE_H
#define SHOPPINGLIKEFILES_NATIVECOMPONENT_DLLPUBLICINTERFACE_H

#include "CAFF_Processor.h"

#ifdef __cplusplus
extern "C" {
#endif
CAFF::CAFFProcessor *CreateCaffProcessor();
void DeleteCaffProcessor(CAFF::CAFFProcessor *proc);

bool ValidateFile(CAFF::CAFFProcessor *proc);
CIFF::Pixel *GenerateThumbnail(CAFF::CAFFProcessor *proc);
CAFF::Credit GetCredit(CAFF::CAFFProcessor *proc);
void GetTags(CAFF::CAFFProcessor *proc);
#ifdef __cplusplus
}
#endif

#endif //SHOPPINGLIKEFILES_NATIVECOMPONENT_DLLPUBLICINTERFACE_H
