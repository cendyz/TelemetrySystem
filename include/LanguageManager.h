#pragma once
#include <string>
#include <unordered_map>

class LanguageManager {
public:
  explicit LanguageManager(std::string_view lang);
  ~LanguageManager() = default;

  std::unordered_map<std::string, std::string> dictionary;

private:
  static constexpr std::string enDict{"en"};
  static constexpr std::string jpDict{"jp"};
  std::string dictLang;

  [[nodiscard]] bool isDictExists(const std::string &lang);
  static constexpr std::string dictsPath{"../data/"};
  static constexpr std::string fileType{".txt"};
  std::string dictPath;

  void loadDict();
  void runMissingFileError();
  static constexpr std::string_view fileNotFoundMsg{
      "Error: Dictionary not found."};
  static constexpr std::string_view descFileNotFoundMsg{
      "The 'data' folder must contain a file named 'jp.txt' or 'en.txt', which "
      "is available for download in the 'dictionary' folder."};

  static constexpr std::string_view bracketSystemMsg{"[SYSTEM]"};
  static constexpr std::string_view loadingMsg{"Loading..."};
};
