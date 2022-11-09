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
    const char *c = "RandomText\0ab\0";
    std::vector vec = getTags((uint8_t *) c, 0, 20);
    std::string s;
    for (int i = 0; i < vec.size(); i++) {
        s.append(vec[i]);
        if (i != vec.size() - 1)
            s += '\0';
    }
    std::string expected(c, c + 14);
    ASSERT_EQ(s, expected);
}