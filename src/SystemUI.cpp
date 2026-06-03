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

void SystemUI::printInitializationMessages() const {
    for (size_t i{}; i < systems_k.size(); ++i) {
        Utils::printMessageWithSpace(langManager->dictionary.at(systems_k[i]));
        Utils::printColorfulMessage(langManager->dictionary.at(inits_k[i]),
                                    COLORS::CYAN);
        Utils::pauseOutputForSec();
    }
}

void SystemUI::printVehiclesFileIsEmpty() const {
    Utils::printColorfulMessage(langManager->dictionary["EMPTY"], COLORS::RED);
}

void SystemUI::printAddedVehicle(
    const std::vector<std::unique_ptr<Vehicle> > &vehicles,
    const std::string_view electricCar) const {
    for (auto &vehicle: vehicles) {
        Utils::printMessageWithSpace(langManager->dictionary["S_INFO"]);
        if (vehicle->type != electricCar) {
            Utils::printMessageWithSpace(
                langManager->dictionary["ADD_COMBUSTION"]);
            Utils::printColorfulMessage(vehicle->name, COLORS::BROWN);
        } else {
            Utils::printMessageWithSpace(langManager->dictionary["ADD_ELECTRIC"]);
            Utils::printColorfulMessage(vehicle->name, COLORS::GREEN);
        }
        Utils::pauseOutputForSec();
    }
}

void SystemUI::printTelemetricSimulation(const std::unique_ptr<Vehicle> &obj) {
    std::cout << '\n';
    Utils::printMessageWithSpace(langManager->dictionary["TICK_START"]);
    Utils::printMessageWithSpace(tickNum);
    Utils::printMessageWithSpace(langManager->dictionary["REST"]);
    Utils::printMessageNewLine(langManager->dictionary["TICK_END"]);
    Utils::printMessageWithSpace(langManager->dictionary["TELEMETRY"]);
    std::cout << obj->name << ":" << '\n';
    Utils::printMessageWithSpace(langManager->dictionary["R_ARROW"]);
    Utils::printMessageWithSpace(langManager->dictionary["IS_RUN"]);
    std::cout << std::boolalpha << obj->isON << '\n';
    Utils::printMessageWithSpace(langManager->dictionary["R_ARROW"]);
    Utils::printMessageWithSpace(langManager->dictionary["E_TEMP"]);
    Utils::printMessageNewLine(obj->enginePower);
    Utils::printMessageWithSpace(langManager->dictionary["R_ARROW"]);
    Utils::printMessageWithSpace(langManager->dictionary["F_LEVEL"]);
    Utils::printMessageNewLine(obj->fuel);
    ++tickNum;
}
