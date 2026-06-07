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
                                    COLORS::YELLOW);
        Utils::pauseOutputForXSec(1);
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
            Utils::printColorfulMessage(vehicle->name, COLORS::BLU);
        } else {
            Utils::printMessageWithSpace(langManager->dictionary["ADD_ELECTRIC"]);
            Utils::printColorfulMessage(vehicle->name, COLORS::MAGNETA);
        }
        Utils::pauseOutputForXSec(1);
    }
}

void SystemUI::printTelemetricSimulation(const std::unique_ptr<Vehicle> &obj) const {
    const std::string_view color{(obj->type == electricCarType) ? COLORS::BLU : COLORS::MAGNETA};
    printCarNameInfo(obj->name, color, obj->isON, obj->fuel);
    printIsRunning(obj->isON);
    printEngineTemp(obj->engineTemp);
    printFuel(obj->fuel);
}

void SystemUI::printSimulationStartHeader() {
    Utils::printMessageWithSpace(langManager->dictionary["TICK_START"]);
    Utils::printMessageWithSpace(tickNum++);
    Utils::printMessageNewLine(langManager->dictionary["TICK_END"]);
}

void SystemUI::printCarNameInfo(const std::string &name, const std::string_view color,
                                const bool &isOn, const double fuel) const {
    Utils::printMessageWithSpace(langManager->dictionary["TELEMETRY"]);
    std::cout << color << name << COLORS::RESET << " ";
    if (isOn && fuel > 0) {
        std::cout << langManager->dictionary["RUN"] << ":" << '\n';
    } else {
        std::cout << langManager->dictionary["REST"] << ":" << '\n';
    }
}

void SystemUI::printIsRunning(const bool isOn) const {
    const std::string_view engine{isOn ? "1.0" : "0.0"};
    const std::string_view color{isOn ? COLORS::GREEN : COLORS::L_YELLOW};
    const std::string label{
        langManager->dictionary["R_ARROW"] + " "
        + langManager->dictionary["IS_RUN"]
    };
    Utils::printRow(label, engine, color);
}

void SystemUI::printEngineTemp(const double temp) const {
    const std::string_view color{
        (temp <= normalEngTemp)
            ? COLORS::WHITE
            : (temp > dangerEngTemp)
                  ? COLORS::RED
                  : COLORS::L_YELLOW
    };
    const std::string label{
        langManager->dictionary["R_ARROW"] + " " +
        langManager->dictionary["E_TEMP"]
    };
    std::cout << std::fixed << std::setprecision(2);
    Utils::printRow(label, temp, color);
}

void SystemUI::printFuel(const double fuel) const {
    const std::string_view color{
        (fuel <= 20)
            ? COLORS::RED
            : (fuel > 20 && fuel <= 40)
                  ? COLORS::L_YELLOW
                  : (fuel >= 75)
                        ? COLORS::GREEN
                        : COLORS::WHITE
    };

    const std::string label{
        langManager->dictionary["R_ARROW"] + " " +
        langManager->dictionary["F_LEVEL"]
    };
    Utils::printRow(label, fuel, color);
}

void SystemUI::printEngineWarning() const {
    Utils::printMessageWithSpace(langManager->dictionary["WARNING"]);
    Utils::printColorfulMessage(langManager->dictionary["DANGER_TEMP"], COLORS::RED);
}
