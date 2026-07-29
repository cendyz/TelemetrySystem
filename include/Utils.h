#pragma once

#include "Colors.h"
#include <chrono>
#include <csignal>
#include <format>
#include <iostream>
#include <regex>
#include <string>
#include <thread>

namespace Utils
{
inline std::regex langInputRegex{"^(jp|en)$", std::regex::icase};

inline volatile std::sig_atomic_t interrupted{0};
void pauseOutputForOneSec();

template <typename T> void printMessageNewLine(const T& msg)
{
    std::cout << msg << '\n';
}

void printNewLine();

void printMessage(std::string_view msg);

template <typename T> void printMessageWithSpace(const T& msg)
{
    std::cout << msg << " ";
}

template <typename T> void printColorfulMessageNewLine(const T& mess, const std::string_view color)
{
    std::cout << color << mess << COLORS::RESET << '\n';
}

template <typename T> void printColorfulMessage(const T& mess, const std::string_view color)
{
    std::cout << color << mess << COLORS::RESET;
}

void lowerString(std::string& text);

[[nodiscard]] bool isLangInputCorrect(const std::string& input);

template <typename T> void printRow(const std::string_view label, const T& value, const std::string_view color)
{
    std::cout << std::format("{:>20}", label);
    std::cout << color;
    if constexpr (std::is_floating_point_v<T>)
    {
        std::cout << std::format("{:>7.2f}", value);
    }
    else
    {
        std::cout << std::format("{:>7}", value);
    }
    std::cout << COLORS::RESET << '\n';
}

void printLabel(std::string_view label, std::string_view color);
} // namespace Utils
