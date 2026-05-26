#pragma once
#include <string>
#include <unordered_map>

class LanguageManager {
public:
    LanguageManager() = default;
    ~LanguageManager() = default;

    std::unordered_map<std::string, std::string> dictionary;

private:

    static constexpr std::string_view bracketSystemMsg{"[SYSTEM]"};
    static constexpr std::string_view loadingMsg{"Loading..."};
};
