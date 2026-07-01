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
        Utils::printLabel(langManager->getText(systems_k[i]), COLORS::YELLOW);
        Utils::printMessageNewLine(langManager->getText(inits_k[i]));
        Utils::pauseOutputForXSec(1);
    }
}

void SystemUI::printVehiclesFileIsEmpty() const {
    Utils::printColorfulMessageNewLine(langManager->getText("EMPTY"), COLORS::RED);
}

void SystemUI::printAddedVehicle(
    const std::vector<std::unique_ptr<Vehicle> > &vehicles) const {
    for (auto &vehicle: vehicles) {
        Utils::printLabel(langManager->getText("S_INFO"), COLORS::YELLOW);
        if (vehicle->getType() != Vehicle::Type::ElectricVehicle) {
            Utils::printMessageWithSpace(langManager->getText("ADD_COMBUSTION"));
            Utils::printColorfulMessageNewLine(vehicle->getName(), COLORS::BLU);
        } else {
            Utils::printMessageWithSpace(langManager->getText("ADD_ELECTRIC"));
            Utils::printColorfulMessageNewLine(vehicle->getName(), COLORS::MAGNETA);
        }

        Utils::pauseOutputForXSec(1);
    }
}

void SystemUI::printTelemetricSimulation(const std::unique_ptr<Vehicle> &obj) const {
    const std::string_view color{obj->getType() == Vehicle::Type::ElectricVehicle ? COLORS::BLU : COLORS::MAGNETA};
    printCarNameInfo(obj->getName(), color, obj->getIsOn(), obj->getFuel());
    printIsRunning(obj->getIsOn());
    printEngineTemp(obj->getEngineTemp(), obj->getWarningTemp(), obj->getDangerTemp());
    printFuel(obj);
    Utils::printNewLine();
}

void SystemUI::printSimulationStartHeader() {
    Utils::printNewLine();
    Utils::printMessageWithSpace(langManager->getText("TICK_START"));
    Utils::printMessageWithSpace(tickNum++);
    Utils::printMessageNewLine(langManager->getText("TICK_END"));
    Utils::printNewLine();
}

void SystemUI::printCarNameInfo(const std::string_view name, const std::string_view color,
                                const bool &isOn, const double fuel) const {
    Utils::printMessageWithSpace(langManager->getText("TELEMETRY"));
    std::cout << color << name << COLORS::RESET << " ";
    if (isOn && fuel > 0) {
        std::cout << langManager->getText("RUN") << ":";
        Utils::printNewLine();
    } else {
        std::cout << langManager->getText("REST") << ":";
        Utils::printNewLine();
    }
}

void SystemUI::printIsRunning(const bool isOn) const {
    const std::string_view engine{isOn ? "1.0" : "0.0"};
    const std::string_view color{isOn ? COLORS::GREEN : COLORS::L_YELLOW};
    Utils::printRow(getArrowMsg(langManager->getText("IS_RUN")), engine, color);
}

void SystemUI::printEngineTemp(const double temp, const double warningTemp, const double dangerTemp) const {
    const std::string_view color{
        temp <= warningTemp
            ? COLORS::WHITE
            : temp >= dangerTemp
                  ? COLORS::RED
                  : COLORS::L_YELLOW
    };
    Utils::printRow(getArrowMsg(langManager->getText("E_TEMP")), temp, color);
}

void SystemUI::printFuel(const std::unique_ptr<Vehicle> &obj) const {
    const std::string_view color{
        obj->getFuel() <= obj->getLowFuel()
            ? COLORS::RED
            : obj->getFuel() > obj->getMediumFuel() && obj->getFuel() <= obj->getMediumFuel()
                  ? COLORS::L_YELLOW
                  : obj->getFuel() >= obj->getHighFuel()
                        ? COLORS::GREEN
                        : COLORS::WHITE
    };

    Utils::printRow(getArrowMsg(langManager->getText("F_LEVEL")), obj->getFuel(), color);
}

std::string SystemUI::getArrowMsg(const std::string &msg) const {
    return langManager->getText("R_ARROW") + " " + msg;
}

void SystemUI::printEngineWarning() const {
    Utils::printLabel(langManager->getText("WARNING"), COLORS::YELLOW);
    Utils::printMessageNewLine(langManager->getText("WARNING_TEMP"));
}

void SystemUI::printEngineDanger() const {
    Utils::printLabel(langManager->getText("ALERT"), COLORS::RED);
    Utils::printMessageNewLine(langManager->getText("DANGER_TEMP"));
}

void SystemUI::printMediumFuelLevel() const {
    Utils::printLabel(langManager->getText("WARNING"), COLORS::YELLOW);
    Utils::printMessageNewLine(langManager->getText("MEDIUM_FUEL"));
}

void SystemUI::printLowFuelLevel() const {
    Utils::printLabel(langManager->getText("ALERT"), COLORS::RED);
    Utils::printMessageNewLine(langManager->getText("LOW_FUEL"));
}

void SystemUI::printNoFuel() const {
    Utils::printLabel(langManager->getText("ALERT"), COLORS::RED);
    Utils::printMessageNewLine(langManager->getText("NO_FUEL"));
}

void SystemUI::pritnAllOkInfo() const {
    Utils::printLabel(langManager->getText("INFO"), COLORS::GREEN);
    Utils::printMessageNewLine(langManager->getText("FINE"));
}
