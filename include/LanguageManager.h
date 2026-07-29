#pragma once
#include <array>
#include <filesystem>
#include <string>
#include <unordered_map>

class LanguageManager
{
  public:
    explicit LanguageManager();

    [[nodiscard]] static std::string_view getText(const std::string&& key);
    [[nodiscard]] static std::string_view getText(const std::string& key);
    [[nodiscard]] static std::array<std::string, 2> getSystemsInfo();
    [[nodiscard]] static std::array<std::string, 2> getInitsInfo();

  private:
    void setLanguage();
    [[nodiscard]] static bool itIsJapaneseLanguage();
    [[nodiscard]] static std::string getSystemLang();

    static constexpr std::string_view enDict{"en"};
    static constexpr std::string_view jpDict{"jp"};

    static constexpr std::string_view choseLangInputMsg{"Select the log display language (JP/EN): "};
    static constexpr std::string_view wrongLangInputMsg{"Invalid command."};

    static inline const std::array<std::string, 2> systems_k{"S_BOOT", "S_INFO"};
    static inline const std::array<std::string, 2> inits_k{"INIT", "LANG_L"};

    std::string dictLang;
    inline static std::unordered_map<std::string, std::string> dictionary;

    std::filesystem::path dictsPath{DATA_DIR};
    static constexpr std::string_view fileType{".txt"};

    void loadDict() const;

    static constexpr std::string_view fileNotFoundMsg{"Error: Dictionary not found."};
    static constexpr std::string_view descFileNotFoundMsg{
        "The 'data' folder must contain a file named 'jp.txt' or 'en.txt', which "
        "is available for download in the 'dictionary' folder."};
};
