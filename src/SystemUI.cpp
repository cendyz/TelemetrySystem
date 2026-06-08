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
        Utils::printColorfulMessageNewLine(wrongLangInputMsg, COLORS::RED);
    }
}

void SystemUI::printInitializationMessages() const {
    for (size_t i{}; i < systems_k.size(); ++i) {
        Utils::printMessage("[");
        Utils::printColorfulMessage(langManager->dictionary.at(systems_k[i]), COLORS::YELLOW);
        Utils::printMessage("] ");
        Utils::printMessageNewLine(langManager->dictionary.at(inits_k[i]));
        Utils::pauseOutputForXSec(1);
    }
}

void SystemUI::printVehiclesFileIsEmpty() const {
    Utils::printColorfulMessageNewLine(langManager->dictionary["EMPTY"], COLORS::RED);
}

void SystemUI::printAddedVehicle(
    const std::vector<std::unique_ptr<Vehicle> > &vehicles,
    const std::string_view electricCar) const {
    for (auto &vehicle: vehicles) {
        std::cout << "[";
        Utils::printColorfulMessage(langManager->dictionary["S_INFO"], COLORS::YELLOW);
        std::cout <<"] ";
        if (vehicle->type != electricCar) {
            Utils::printMessageWithSpace(
                langManager->dictionary["ADD_COMBUSTION"]);
            Utils::printColorfulMessageNewLine(vehicle->name, COLORS::BLU);
        } else {
            Utils::printMessageWithSpace(langManager->dictionary["ADD_ELECTRIC"]);
            Utils::printColorfulMessageNewLine(vehicle->name, COLORS::MAGNETA);
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
    std::cout << '\n';
}

void SystemUI::printSimulationStartHeader() {
    Utils::printMessageWithSpace(langManager->dictionary["TICK_START"]);
    Utils::printMessageWithSpace(tickNum++);
    Utils::printMessageNewLine(langManager->dictionary["TICK_END"]);
    std::cout << '\n';
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
        (temp <= warningEngTemp)
            ? COLORS::WHITE
            : (temp >= dangerEngTemp)
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
        (fuel <= lowFuel)
            ? COLORS::RED
            : (fuel > mediumFuel && fuel <= mediumFuel)
                  ? COLORS::L_YELLOW
                  : (fuel >= highFuel)
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
    std::cout << "[";
    Utils::printColorfulMessage(langManager->dictionary["WARNING"], COLORS::YELLOW);
    std::cout << "] ";
    Utils::printMessageNewLine(langManager->dictionary["WARNING_TEMP"]);
}

void SystemUI::printEngineDanger() const {
    std::cout << "[";
    Utils::printColorfulMessage(langManager->dictionary["ALERT"], COLORS::RED);
    std::cout << "] ";
    Utils::printMessageNewLine(langManager->dictionary["DANGER_TEMP"]);
}

void SystemUI::printMediumFuelLevel() const {
    std::cout << "[";
    Utils::printColorfulMessage(langManager->dictionary["WARNING"], COLORS::YELLOW);
    std::cout << "] ";
    Utils::printMessageNewLine(langManager->dictionary["MEDIUM_FUEL"]);
}

void SystemUI::printLowFuelLevel(const std::string &type) const {
    std::cout << "[";
    Utils::printColorfulMessage(langManager->dictionary["ALERT"], COLORS::RED);
    std::cout << "] ";
    if (type == electricCarType) {
        Utils::printMessageNewLine(langManager->dictionary["LOW_FUEL_ELE"]);
    } else {
        Utils::printMessageNewLine(langManager->dictionary["LOW_FUEL_COMB"]);
    }
}

void SystemUI::printNoFuel() const {
    std::cout << "[";
    Utils::printColorfulMessage(langManager->dictionary["INFO"], COLORS::RED);
    std::cout << "] ";
    Utils::printMessageNewLine(langManager->dictionary["NO_FUEL"]);
}

void SystemUI::pritnAllOkInfo() const {
    std::cout << "[";
    Utils::printColorfulMessage(langManager->dictionary["INFO"], COLORS::GREEN);
    std::cout << "] ";
    Utils::printMessageNewLine(langManager->dictionary["FINE"]);
}
