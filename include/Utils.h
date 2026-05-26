#pragma once
#include "Colors.h"
#include <iostream>
#include <string>

namespace Utils {
    inline void printErrorMessage(std::string_view mess) {
        std::cout << COLORS::RED << mess << COLORS::RESET << '\n';
    }

    inline void lowerString(std::string &text) {
        for (char &c : text) {
            c = c & '_';
        }
    }
}