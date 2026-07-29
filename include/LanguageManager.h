#pragma once
#include <array>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace LanguageManager
{
[[nodiscard]] std::string_view getText(const std::string& key);
[[nodiscard]] std::array<std::string, 2> getSystemsInfo();
[[nodiscard]] std::array<std::string, 2> getInitsInfo();

void setLanguage();
[[nodiscard]] bool itIsJapaneseLanguage();
[[nodiscard]] std::string getSystemLang();

constexpr std::string_view enDict{"en"};
constexpr std::string_view jpDict{"jp"};

constexpr std::string_view choseLangInputMsg{"Select the log display language (JP/EN): "};
constexpr std::string_view wrongLangInputMsg{"Invalid command."};

inline const std::array<std::string, 2> systems_k{"S_BOOT", "S_INFO"};
inline const std::array<std::string, 2> inits_k{"INIT", "LANG_L"};

inline std::unordered_map<std::string, std::string> dictionary;

inline std::filesystem::path dictsPath{DATA_DIR};
constexpr std::string_view fileType{".txt"};

void loadDict();
}; // namespace LanguageManager
