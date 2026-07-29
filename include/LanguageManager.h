#pragma once
#include <array>
#include <filesystem>
#include <regex>
#include <string>
#include <unordered_map>

class LanguageManager
{
  public:
    LanguageManager();

    [[nodiscard]] static std::string_view getText(const std::string& key);
    [[nodiscard]] std::array<std::string, 2> getSystemsInfo() const;
    [[nodiscard]] std::array<std::string, 2> getInitsInfo() const;

    void setLanguage();
    [[nodiscard]] bool itIsJapaneseLanguage() const;
    [[nodiscard]] std::string getSystemLang() const;

  private:
    const std::string_view enDict{"en"};
    const std::string_view jpDict{"jp"};

    std::regex langInputRegex{"^(jp|en)$", std::regex::icase};
    [[nodiscard]] bool isLangInputCorrect(const std::string& input) const;

    const std::string_view choseLangInputMsg{"Select the log display language (JP/EN): "};
    const std::string_view wrongLangInputMsg{"Invalid command."};

    const std::array<std::string, 2> systems_k{"S_BOOT", "S_INFO"};
    const std::array<std::string, 2> inits_k{"INIT", "LANG_L"};

    inline static std::unordered_map<std::string, std::string> dictionary{};

    std::filesystem::path dictsPath{DATA_DIR};
    std::string_view fileType{".txt"};

    void loadDict() const;
};
