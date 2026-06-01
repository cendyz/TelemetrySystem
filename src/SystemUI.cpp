#include "../include/SystemUI.h"
#include "../include/Utils.h"
#include "Colors.h"
#include "LanguageManager.h"
#include <iostream>
#include <memory>

SystemUI::SystemUI() { setLanguage(); }

void SystemUI::setLanguage() {
  if (itIsJapaneseLanguage()) {
    langManager = std::make_unique<LanguageManager>(jpLen);
  } else {
    langManager = std::make_unique<LanguageManager>(enLen);
  }
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

void SystemUI::printInitializationMessages() const  {
  for(size_t i{}; i < systems_k.size(); ++i) {
      Utils::printMessageWithSpace(langManager->dictionary.at(systems_k[i]));
      Utils::printColorfulMessage(langManager->dictionary.at(inits_k[i]), COLORS::CYAN);
      Utils::pauseOutputForSec();
  }
}

void SystemUI::printLoad() {
  while (true) {
    Utils::printMessageWithSpace("[" + langManager->dictionary.at("SYSTEM") +
                                 "]");
    Utils::printColorfulMessage(langManager->dictionary.at("LOADING"),
                                COLORS::YELLOW);
  }
}

void SystemUI::printVehiclesFileIsEmpty() const {
    Utils::printColorfulMessage(langManager->dictionary.at("EMPTY"), COLORS::RED);
}
