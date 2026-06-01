#pragma once
#include <string_view>

namespace COLORS {
    inline constexpr std::string_view RED{"\033[31m"};
    inline constexpr std::string_view CYAN{"\033[94m"};
    inline constexpr std::string_view YELLOW{"\033[33m"};
    inline constexpr std::string_view RESET{"\033[0m"};
}