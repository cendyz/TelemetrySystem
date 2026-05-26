#include "SystemUI.h"
#include <iostream>

#include "Japanese.h"
#include "English.h"
#include "Utils.h"

SystemUI::SystemUI() {
}

void SystemUI::setLanguage() {
    if (itIsJapaneseLanguage()) {
        logLang = std::make_unique<Japanese>();
    } else {
        logLang = std::make_unique<English>();
    }
    logLang->te
}

bool SystemUI::itIsJapaneseLanguage() {
    return getSystemLang() == jpLen;
}

std::string SystemUI::getSystemLang() {
    std::string input;
    while (true) {
        getline(std::cin, input);
        if (isLangInputCorrect(input)) {
            Utils::lowerString(input);
            return input;
        }
        Utils::printErrorMessage(wrongLangInputMsg);
    }
}

bool SystemUI::isLangInputCorrect(const std::string &input) {
    return std::regex_match(input, langInputRegex);
}

void SystemUI::printLoad() {
    logLang->
}
