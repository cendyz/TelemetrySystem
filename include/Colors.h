#pragma once
#include <string_view>

namespace COLORS {
    inline constexpr std::string_view RED{"\033[91m"};
    inline constexpr std::string_view CYAN{"\033[94m"};
    inline constexpr std::string_view GREEN{"\033[92m"};
    inline constexpr std::string_view L_YELLOW{"\033[93m"};
    inline constexpr std::string_view BLU{"\033[96m"};
    inline constexpr std::string_view MAGNETA{"\033[95m"};
    inline constexpr std::string_view YELLOW{"\033[33m"};
    inline constexpr std::string_view WHITE{"\033[97m"};
    inline constexpr std::string_view RESET{"\033[0m"};
} // namespace COLORS
