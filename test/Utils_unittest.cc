//
// Created by daysm on 09/11/2022.
//

#include <gtest/gtest.h>
#include <Utils.h>

TEST(UTILS_SUITE, getBlockTypeTest){
    ASSERT_EQ(CAFF::Utils::getBlockType(0x01) , CAFF::Utils::CAFF_Block_Type::Header );
    ASSERT_EQ(CAFF::Utils::getBlockType(0x02) , CAFF::Utils::CAFF_Block_Type::Credits );
    ASSERT_EQ(CAFF::Utils::getBlockType(0x03) , CAFF::Utils::CAFF_Block_Type::Animation );
    ASSERT_EQ(CAFF::Utils::getBlockType(0x04) , CAFF::Utils::CAFF_Block_Type::Unknown );
}

TEST(UTILS_SUITE,  INT64Test){
    uint64_t v = 10;
    char *char_array = static_cast<char*>(static_cast<void*>(&v));
    std::vector<char> vec;
    char char_array2[8];
    size_t i = 0;
    while ( i < 8 ){
        vec.push_back(*(char_array+i));
        char_array2[i] = *(char_array+i);
        i++;
    }

    auto t1 = new NativeComponent::Types::INT64(v);
    ASSERT_EQ(t1->getValue(), v);

    auto t2 = new NativeComponent::Types::INT64(char_array2);
    ASSERT_EQ(t2->getValue(), v);

    NativeComponent::Types::INT64 t3;
    t3.FromArray(vec);
    ASSERT_EQ(v, t3.getValue());

}

TEST(UTILS_SUITE,  GetDataTest){
    uint64_t v = 10;
    char *char_array = static_cast<char*>(static_cast<void*>(&v));
    uint64_t test;
    GetData(reinterpret_cast<unsigned char *>(char_array), 0, 8, &test);
    ASSERT_EQ(test, v);
}