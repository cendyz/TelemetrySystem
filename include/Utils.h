#pragma once

#include "Colors.h"
#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <thread>

namespace Utils {
    inline static std::regex langInputRegex{"^(jp|en)$", std::regex::icase};

    inline void checkOS(std::string & pathToCorrect) {
#ifdef _WIN32
        pathToCorrect = "../" + pathToCorrect;
#endif
    }

    inline void pauseOutputForXSec(int &&sec) {
        std::this_thread::sleep_for(std::chrono::seconds(sec));
    }

    template<typename T>
    static void printMessageNewLine(const T &msg) {
        std::cout << msg << '\n';
    }

    inline void printMessage(const std::string_view msg) { std::cout << msg; }

    template<typename T>
    void printMessageWithSpace(const T &msg) {
        std::cout << msg << " ";
    }

    template<typename T>
    static void printColorfulMessageNewLine(const T &mess,
                                     const std::string_view color) {
        std::cout << color << mess << COLORS::RESET << '\n';
    }

    template<typename T>
    static void printColorfulMessage(const T &mess,
                                     const std::string_view color) {
        std::cout << color << mess << COLORS::RESET;
    }

    inline void lowerString(std::string &text) {
        for (char &c: text) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
    }

    [[nodiscard]] inline bool isLangInputCorrect(const std::string &input) {
        return std::regex_match(input, langInputRegex);
    }

    template<typename T>
    static void printRow(const std::string &label, const T &value, const std::string_view color) {
        std::cout << std::right << std::setw(20) << label;
        std::cout << color;
        std::cout << std::right << std::setw(7) << value;
        std::cout << COLORS::RESET << '\n';
    }
} // namespace Utils
