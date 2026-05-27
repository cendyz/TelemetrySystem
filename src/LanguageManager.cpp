#include "../include/LanguageManager.h"
#include "Colors.h"
#include "Utils.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

LanguageManager::LanguageManager(std::string_view lang) {
  if (lang == jpDict) {
    dictLang = jpDict;
  } else {
    dictLang = enDict;
  }

  if (isDictExists(dictLang)) {
    loadDict();
  } else {
    runMissingFileError();
  }
}

bool LanguageManager::isDictExists(const std::string &lang) {
  dictPath = dictsPath + lang + fileType;

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

    dictionary.try_emplace(key, value);
  }
}

void LanguageManager::runMissingFileError() {
  Utils::printColorfulMessage(fileNotFoundMsg, COLORS::RED);
  Utils::printColorfulMessage(descFileNotFoundMsg, COLORS::RED);
  std::exit(EXIT_FAILURE);
}
