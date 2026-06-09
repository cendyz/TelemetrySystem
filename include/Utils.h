#pragma once

#include "Colors.h"
#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <format>

namespace Utils {
    inline static std::regex langInputRegex{"^(jp|en)$", std::regex::icase};

    inline void pauseOutputForXSec(int &&sec) {
        std::this_thread::sleep_for(std::chrono::seconds(sec));
    }

    template<typename T>
    void printMessageNewLine(const T &msg) {
        std::cout << msg << '\n';
    }

    inline void printMessage(const std::string_view msg) { std::cout << msg; }

    template<typename T>
    void printMessageWithSpace(const T &msg) {
        std::cout << msg << " ";
    }

    template<typename T>
    void printColorfulMessageNewLine(const T &mess,
                                     const std::string_view color) {
        std::cout << color << mess << COLORS::RESET << '\n';
    }

    template<typename T>
    void printColorfulMessage(const T &mess,
                              const std::string_view color) {
        std::cout << color << mess << COLORS::RESET;
    }

    inline void lowerString(std::string &text) {
        std::ranges::transform(text.begin(), text.end(),
                               text.begin(), [](const char &c) { return tolower(c); });
    }

    [[nodiscard]] inline bool isLangInputCorrect(const std::string &input) {
        return std::regex_match(input, langInputRegex);
    }

    template<typename T>
    void printRow(const std::string &label, const T &value, const std::string_view color) {
        std::cout << std::right << std::format("{:>20}", label);
        std::cout << color;
        if constexpr (std::is_floating_point_v<T>) {
            // 1. Obsługa ułamków (float, double) - 2 miejsca po przecinku, do prawej
            std::cout << std::format("{:>7.2f}", value);
        } else {
            // 3. Obsługa wszystkiego innego (np. int, bool) - zwykłe wyrównanie do prawej
            std::cout << std::format("{:>7}", value);
        }
        std::cout << COLORS::RESET << '\n';
    }

    inline void printLabel(const std::string_view label, const std::string_view color) {
        std::cout << "[";
        printColorfulMessage(label, color);
        std::cout << "] ";
    }
} // namespace Utils
