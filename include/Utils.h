#pragma once
#include "Colors.h"
#include <cctype>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <chrono>

namespace Utils {
inline static std::regex langInputRegex{"^(jp|en)$", std::regex::icase};

inline static void pauseOutputForSec() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

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
    c = std::tolower(c);
  }
}

[[nodiscard]] inline bool isLangInputCorrect(const std::string &input) {
  return std::regex_match(input, langInputRegex);
}

} // namespace Utils
