#include "../include/LanguageManager.h"
#include "Colors.h"
#include "Utils.h"
#include <filesystem>
#include <fstream>
#include <sstream>
namespace fs = std::filesystem;

LanguageManager::LanguageManager(const std::string_view lang)
{
    if (lang == jpDict)
    {
        dictsPath += std::string(jpDict) + fileType.data();
    }
    else
    {
        dictsPath += std::string(enDict) + fileType.data();
    }
    loadDict();
}

void LanguageManager::loadDict()
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

std::string_view LanguageManager::getText(const std::string& key)
{
    return dictionary.at(key);
}
