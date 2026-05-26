#pragma once
#include "LanguageManager.h"
#include <memory>
#include <string>
#include <regex>

class SystemUI {
public:
    SystemUI();

    ~SystemUI() = default;

private:
    std::unique_ptr<LanguageManager> logLang;

    [[nodiscard]] static std::string getSystemLang();
    static constexpr std::string_view choseLangInputMsg{
        "Select the log display language (JP/EN): "
    };
    static constexpr std::string_view jpLen{"jp"};
    static constexpr std::string_view enLen{"en"};

    [[nodiscard]] static bool isLangInputCorrect(const std::string &input);
    inline static std::regex langInputRegex{"^(jp|en)$"};
    static constexpr std::string_view wrongLangInputMsg{"Invalid command."};
    [[nodiscard]] static bool itIsJapaneseLanguage();

    void setLanguage();

    void printLoad();
};
