#include "Utils.h"

void Utils::pauseOutputForXSec(int&& sec)
{
    for (size_t i{}; i < 100 && interrupted == 0; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sec));
    }
}

void Utils::printNewLine()
{
    std::cout << '\n';
}

void Utils::printMessage(const std::string_view msg)
{
    std::cout << msg;
}

void Utils::lowerString(std::string& text)
{
    std::ranges::transform(text.begin(), text.end(), text.begin(),
                           [](const char& c)
                           {
                               return tolower(c);
                           });
}

bool Utils::isLangInputCorrect(const std::string& input)
{
    return std::regex_match(input, langInputRegex);
}

void Utils::printLabel(const std::string_view label, const std::string_view color)
{
    std::cout << "[";
    printColorfulMessage(label, color);
    std::cout << "] ";
}
