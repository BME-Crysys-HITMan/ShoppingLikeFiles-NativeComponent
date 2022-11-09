//
// Created by daysm on 09/11/2022.
//

# include <gtest/gtest.h>
# include <CIFF_Utils.h>

TEST(CIFF_UTILS_SUITE, getCaptionTest) {
    const char *c = "RandomText\nasd\0";
    std::string s = getCaption((uint8_t *) c, 0, 20);

    ASSERT_EQ(s, std::string(c, c + 11));
}

TEST(CIFF_UTILS_SUITE, getTagsLength) {
    int header = 40;
    ASSERT_EQ(0, getTagsLength(header, 4));
}

TEST(CIFF_UTILS_SUITE, getTagsTest) {
    const char *c = "RandomText\0ab";
    std::vector vec = getTags((uint8_t *) c, 0, 14);
    std::vector<std::string> expected = {"RandomText", "ab"};
    ASSERT_EQ(vec, expected);
}