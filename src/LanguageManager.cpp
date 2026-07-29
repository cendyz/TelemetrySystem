#include "../include/LanguageManager.h"
#include "Colors.h"
#include "Utils.h"
#include <filesystem>
#include <fstream>
#include <sstream>
namespace fs = std::filesystem;

LanguageManager::LanguageManager()
{
    setLanguage();
    loadDict();
}

void LanguageManager::setLanguage()
{
    if (itIsJapaneseLanguage())
    {
        dictsPath += std::string(jpDict) + fileType.data();
    }
    else
    {
        dictsPath += std::string(enDict) + fileType.data();
    }
}

bool LanguageManager::itIsJapaneseLanguage()
{
    return getSystemLang() == jpDict;
}
std::string LanguageManager::getSystemLang()
{
    std::string input;
    while (true)
    {
        Utils::printMessage(choseLangInputMsg);
        getline(std::cin, input);
        if (Utils::isLangInputCorrect(input))
        {
            Utils::lowerString(input);
            return input;
        }
        Utils::printColorfulMessageNewLine(wrongLangInputMsg, COLORS::RED);
    }
}
void LanguageManager::loadDict() const
{
    std::ifstream dict{dictsPath};

    std::string line;
    std::string key;
    std::string value;

    while (getline(dict, line))
    {
        std::stringstream ss(line);
        getline(ss, key, ';');
        getline(ss, value, ';');

        dictionary.try_emplace(std::move(key), std::move(value));
    }
}

std::array<std::string, 2> LanguageManager::getInitsInfo()
{
    return inits_k;
}

std::array<std::string, 2> LanguageManager::getSystemsInfo()
{
    return systems_k;
}

std::string_view LanguageManager::getText(const std::string&& key)
{
    return dictionary.at(key);
}
std::string_view LanguageManager::getText(const std::string& key)
{
    return dictionary.at(key);
}
