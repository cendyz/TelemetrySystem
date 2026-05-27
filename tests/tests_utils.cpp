#include <gtest/gtest.h>
#include "../include/Utils.h"


TEST(lowerString, isLoweringString) {
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


TEST(checkInputLang, IsLangInputCorrect_ValidJapaneseEnglishFormat_ReturnsTrue) {
    std::string text1{"jp"};
    std::string text2{"jP"};
    std::string text3{"Jp"};
    std::string text4{"JP"};

    std::string lext1{"en"};
    std::string lext2{"En"};
    std::string lext3{"eN"};
    std::string lext4{"EN"};

    EXPECT_TRUE(Utils::isLangInputCorrect(text1));
    EXPECT_TRUE(Utils::isLangInputCorrect(text2));
    EXPECT_TRUE(Utils::isLangInputCorrect(text3));
    EXPECT_TRUE(Utils::isLangInputCorrect(text4));
    
    EXPECT_TRUE(Utils::isLangInputCorrect(lext1));
    EXPECT_TRUE(Utils::isLangInputCorrect(lext1));
    EXPECT_TRUE(Utils::isLangInputCorrect(lext1));
    EXPECT_TRUE(Utils::isLangInputCorrect(lext1));
}

TEST(checkInputLang, IsLangInputCorrect_ValidJapaneseEnglishFormat_ReturnsFalse) {
    std::string text1{"23"};
    std::string text2{"j3"};
    std::string text3{"eNN"};
    std::string text4{"jp1"};
    std::string text5{"1en"};
    std::string text6{" en"};
    std::string text7{"jp "};
    std::string text8{"j%"};
    std::string text9{""};
    
    EXPECT_FALSE(Utils::isLangInputCorrect(text1));
    EXPECT_FALSE(Utils::isLangInputCorrect(text2));
    EXPECT_FALSE(Utils::isLangInputCorrect(text3));
    EXPECT_FALSE(Utils::isLangInputCorrect(text4));
    EXPECT_FALSE(Utils::isLangInputCorrect(text5));
    EXPECT_FALSE(Utils::isLangInputCorrect(text6));
    EXPECT_FALSE(Utils::isLangInputCorrect(text7));
    EXPECT_FALSE(Utils::isLangInputCorrect(text8));
    EXPECT_FALSE(Utils::isLangInputCorrect(text9));
}