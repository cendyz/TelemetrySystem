#include "../include/Utils.h"
#include <gtest/gtest.h>

TEST(lowerString, isLoweringString)
{
    std::string text1{"APPLE"};
    std::string text2{"oR3ANg%"};
    std::string text3{"banana"};

    Utils::lowerString(text1);
    Utils::lowerString(text2);
    Utils::lowerString(text3);

    EXPECT_EQ(text1, "apple");
    EXPECT_EQ(text2, "or3ang%");
    EXPECT_EQ(text3, "banana");
}
