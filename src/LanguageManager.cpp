#include "../include/LanguageManager.h"
#include "Colors.h"
#include "Utils.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

LanguageManager::LanguageManager(const std::string_view lang) {
    if (lang == jpDict) {
        dictLang = std::string(jpDict);
    } else {
        dictLang = std::string(enDict);
    }
    if (isDictExists(dictLang)) {
        loadDict();
    } else {
        runMissingFileError();
    }
}

bool LanguageManager::isDictExists(const std::string &lang) {
    dictPath = dictsPath.data() + lang + fileType.data();
    return fs::exists(dictPath);
}

void LanguageManager::loadDict() {
    std::ifstream dict{dictPath};

    std::string line;
    std::string key;
    std::string value;

    while (getline(dict, line)) {
        std::stringstream ss(line);
        getline(ss, key, ';');
        getline(ss, value, ';');

        dictionary.try_emplace(std::move(key), std::move(value));
    }
}

void LanguageManager::runMissingFileError() {
    Utils::printColorfulMessage(fileNotFoundMsg, COLORS::RED);
    Utils::printColorfulMessage(descFileNotFoundMsg, COLORS::RED);
    std::exit(EXIT_FAILURE);
}
