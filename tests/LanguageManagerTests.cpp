#include "LanguageManager.h"
#include "gtest/gtest.h"

namespace
{
class LanguageManagerTests : public LanguageManager
{
  public:
    LanguageManagerTests() : LanguageManager(NotInitTag{}) {}
    using LanguageManager::isLangInputCorrect;
};
} // namespace

TEST(TestDictUserInput, AcceptsCorrectInput)
{
    const LanguageManagerTests obj{};
    EXPECT_TRUE(obj.isLangInputCorrect("jp"));
    EXPECT_TRUE(obj.isLangInputCorrect("JP"));
    EXPECT_TRUE(obj.isLangInputCorrect("eN"));
    EXPECT_TRUE(obj.isLangInputCorrect("en"));
}

TEST(TestDictUserInput, RejectsIncorrectInput)
{
    const LanguageManagerTests obj;
    EXPECT_FALSE(obj.isLangInputCorrect(""));
    EXPECT_FALSE(obj.isLangInputCorrect(" jp"));
    EXPECT_FALSE(obj.isLangInputCorrect("e n"));
    EXPECT_FALSE(obj.isLangInputCorrect("#en2"));
    EXPECT_FALSE(obj.isLangInputCorrect("jp^"));
}