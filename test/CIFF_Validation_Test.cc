//
// Created by kerekesaron on 2022. 11. 09..
//

#include <gtest/gtest.h>
#include "CIFF_validation.h"
#include <algorithm>

class CIFF_Validation : public ::testing::Test {
protected:
    virtual void SetUp() {
        uint8_t validCIFF[]= {
                'C', 'I', 'F', 'F',                      //CIFF
                64,0,0,0,0,0,0,0,        //header_size
                27,0,0,0,0,0,0,0,    //  content_size
                3,0,0,0,0,0,0,0,    // width
                3,0,0,0,0,0,0,0,    // height
                'T', 'E', 'S', 'T', ' ',
                'C','A','P', 'T', 'I',
                'O', 'N','\n',       // caption
                'T', 'A','G', '1', '\0',
                'T', 'A','G', '2', '\0',
                'T', 'A','G', '3', '\0',// tags
                255,0,0,
                0,255,0,
                0, 0,255,
                255,0,0,
                0,255,0,
                0, 0,255,
                255,0,0,
                0,255,0,
                0, 0,255
        };
        std::copy(validCIFF,validCIFF+91, data);
        ciffSize=91;
    }
    uint8_t data[91];
    std::size_t ciffSize;
};

TEST_F(CIFF_Validation, validateHeaderValid){
    ASSERT_TRUE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderWrongMagic){
    data[1]='A';
    ASSERT_FALSE(validateHeader(data));
}


TEST_F(CIFF_Validation, validateHeaderWrongHeaderSize){
    data[4]=63;
    ASSERT_FALSE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderWrongContentSize){
    data[12]=30;
    ASSERT_FALSE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderZeroWidthAndContentSize){
    data[20]=0;
    data[12]=0;
    ASSERT_TRUE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderWrongWidthSize){
    data[20]=2;
    ASSERT_FALSE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderWrongHeightSize){
    data[28]=2;
    ASSERT_FALSE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderNoNewLineInCaption){
    data[48]='n';
    ASSERT_FALSE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderZeroInCaption){
    data[44]='\0';
    ASSERT_FALSE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateHeaderNoEndZeroTagAtLastTag){
    data[63]='0';
    ASSERT_FALSE(validateHeader(data));
}

TEST_F(CIFF_Validation, validateContentValid){
    ASSERT_TRUE(validateContent(data, ciffSize));
}

TEST_F(CIFF_Validation, validateContentValidWithZeroPixels){
    uint8_t emptyContentCiff[64];
    std::copy(data,data+64, emptyContentCiff);
    emptyContentCiff[20]=0;
    emptyContentCiff[12]=0;
    ASSERT_TRUE(validateContent(emptyContentCiff, 64));
}

TEST_F(CIFF_Validation, validateContentWrongCiffSize){
    ASSERT_FALSE(validateContent(data, ciffSize+1));
}


