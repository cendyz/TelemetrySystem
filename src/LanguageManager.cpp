#include "../include/LanguageManager.h"
#include "Colors.h"
#include "Utils.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>
namespace fs = std::filesystem;

LanguageManager::LanguageManager(const std::string_view lang) {
    if (lang == jpDict) {
        dictsPath += std::string(jpDict) + fileType.data();
    } else {
        dictsPath += std::string(enDict) + fileType.data();
    }
    if (isDictExists()) {
        loadDict();
    } else {
        runMissingFileError();
    }
}

bool LanguageManager::isDictExists() const {
    return fs::exists(dictsPath);
}

void LanguageManager::loadDict() {
    std::ifstream dict{dictsPath};

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
