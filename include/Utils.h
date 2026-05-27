#pragma once
#include "Colors.h"
#include <iostream>
#include <regex>
#include <string>

namespace Utils {
inline static std::regex langInputRegex{"^(jp|en)$", std::regex::icase};

inline static void printMessageNewLine(std::string_view msg) {
    std::cout << msg << '\n';
}

inline static void printMessage(std::string_view msg) {
    std::cout << msg;
}

inline static void printMessageWithSpace(std::string_view msg) {
    std::cout << msg << " ";
}

inline void printColorfulMessage(std::string_view mess, std::string_view color) {
  std::cout << color << mess << COLORS::RESET << '\n';
}

inline void lowerString(std::string &text) {
  for (char &c : text) {
    c = c | ' ';
  }
}

[[nodiscard]] inline bool isLangInputCorrect(const std::string &input) {
  return std::regex_match(input, langInputRegex);
}

} // namespace Utils
