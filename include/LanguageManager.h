#pragma once
#include <string>
#include <unordered_map>

class LanguageManager {
public:
    explicit LanguageManager(std::string_view lang);

    ~LanguageManager() = default;

    [[nodiscard]] std::string getText(const std::string &key);

private:
    static constexpr std::string_view enDict{"en"};
    static constexpr std::string_view jpDict{"jp"};
    std::string dictLang;
    std::unordered_map<std::string, std::string> dictionary;

    [[nodiscard]] bool isDictExists() const;

    std::string dictsPath{"data/"};
    static constexpr std::string_view fileType{".txt"};

    void loadDict();

    static void runMissingFileError();

    static constexpr std::string_view fileNotFoundMsg{
        "Error: Dictionary not found."
    };
    static constexpr std::string_view descFileNotFoundMsg{
        "The 'data' folder must contain a file named 'jp.txt' or 'en.txt', which "
        "is available for download in the 'dictionary' folder."
    };
};
