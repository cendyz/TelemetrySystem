#include "../include/SystemUI.h"
#include "../include/Utils.h"
#include "Colors.h"
#include "LanguageManager.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

SystemUI::SystemUI() { setLanguage(); }

void SystemUI::setLanguage() {
  if (itIsJapaneseLanguage()) {
    langManager = std::make_unique<LanguageManager>(jpLen);
  } else {
    langManager = std::make_unique<LanguageManager>(enLen);
  }

  printLoad();
}

bool SystemUI::itIsJapaneseLanguage() { return getSystemLang() == jpLen; }

std::string SystemUI::getSystemLang() {
  std::string input;
  while (true) {
    Utils::printMessage(choseLangInputMsg);
    getline(std::cin, input);
    if (Utils::isLangInputCorrect(input)) {
      Utils::lowerString(input);
      return input;
    }
    Utils::printColorfulMessage(wrongLangInputMsg, COLORS::RED);
  }
}

void SystemUI::printLoad() {
    while(true) {
        Utils::printMessageWithSpace("[" + langManager->dictionary.at("SYSTEM") + "]");
        Utils::printColorfulMessage(langManager->dictionary.at("LOADING"), COLORS::YELLOW);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
