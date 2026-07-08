#pragma once
#include <string>
#include <unordered_map>
#include <filesystem>

class LanguageManager
{
public:
    explicit LanguageManager(std::string_view lang);

    ~LanguageManager() = default;

    [[nodiscard]] static std::string_view getText(const std::string& key);

private:
    static constexpr std::string_view enDict{"en"};
    static constexpr std::string_view jpDict{"jp"};
    inline static std::string dictLang;
    inline static std::unordered_map<std::string, std::string> dictionary;

    inline static std::filesystem::path dictsPath{DATA_DIR};
    static constexpr std::string_view fileType{".txt"};

    inline static void loadDict();

    static constexpr std::string_view fileNotFoundMsg{
        "Error: Dictionary not found."
    };
    static constexpr std::string_view descFileNotFoundMsg{
        "The 'data' folder must contain a file named 'jp.txt' or 'en.txt', which "
        "is available for download in the 'dictionary' folder."
    };
};
