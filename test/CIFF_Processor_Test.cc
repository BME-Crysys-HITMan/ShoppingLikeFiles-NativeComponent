//
// Created by kerekesaron on 2022. 11. 09..
//

#include <gtest/gtest.h>
#include "CIFF_Processor.h"
#include "CIFF_Utils.h"

class CIFF_Process : public ::testing::Test {
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
    CIFF::CIFFProcessor proc;
};

TEST_F(CIFF_Process, ProcessHeaderTest){
    auto header=proc.ProcessHeader(data);
    ASSERT_EQ(header->contentSize, 27);
    ASSERT_EQ(header->headerSize, 64);
    ASSERT_EQ(header->width, 3);
    ASSERT_EQ(header->height, 3);
    ASSERT_EQ(header->caption, "TEST CAPTION");
    std::vector<std::string> tags {"TAG1", "TAG2", "TAG3"};
    ASSERT_EQ(header->tags, tags);
}

TEST_F(CIFF_Process, GetImageTest){
    auto header=proc.ProcessHeader(data);
    auto pixelsFromGetImage=proc.GetImage(data, header);
    CIFF::Pixel pixels[9]={CIFF::Pixel{255,0,0},
                           CIFF::Pixel{0,255,0},
                           CIFF::Pixel{0,0,255},
                           CIFF::Pixel{255,0,0},
                           CIFF::Pixel{0,255,0},
                           CIFF::Pixel{0,0,255},
                           CIFF::Pixel{255,0,0},
                           CIFF::Pixel{0,255,0},
                           CIFF::Pixel{0,0,255}};
    for (int i = 0; i < 9; ++i) {
        ASSERT_EQ(pixelsFromGetImage[i].red, pixels[i].red);
        ASSERT_EQ(pixelsFromGetImage[i].green, pixels[i].green);
        ASSERT_EQ(pixelsFromGetImage[i].blue, pixels[i].blue);
    }
}

TEST_F(CIFF_Process, IsValidValidTest) {
    ASSERT_TRUE(proc.IsValid(data, ciffSize+DURATION_LENGTH));
}

TEST_F(CIFF_Process, IsValidCiffSizeLoverThan36Test) {
    ASSERT_FALSE(proc.IsValid(data, 35));
}

TEST_F(CIFF_Process, IsValidInvalidHeadeTest) {
    data[1]='A';
    ASSERT_FALSE(proc.IsValid(data, ciffSize));
}

TEST_F(CIFF_Process, IsValidInvalidciffSizeTest) {
    ASSERT_FALSE(proc.IsValid(data, ciffSize));
}