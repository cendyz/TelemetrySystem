#pragma once
#include "Colors.h"
#include <cctype>
#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <thread>

namespace Utils {
    inline static std::regex langInputRegex{"^(jp|en)$", std::regex::icase};

    inline void pauseOutputForSec() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    template <typename T>
    static void printMessageNewLine(const T &msg) {
        std::cout << msg << '\n';
    }

    inline void printMessage(const std::string_view msg) { std::cout << msg; }

    template <typename T>
    void printMessageWithSpace(const T& msg) {
        std::cout << msg << " ";
    }

    inline void printColorfulMessage(const std::string_view mess,
                                     const std::string_view color) {
        std::cout << color << mess << COLORS::RESET << '\n';
    }

    inline void lowerString(std::string &text) {
        for (char &c: text) {
            c = std::tolower(c);
        }
    }

    [[nodiscard]] inline bool isLangInputCorrect(const std::string &input) {
        return std::regex_match(input, langInputRegex);
    }
} // namespace Utils
