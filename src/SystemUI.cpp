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
  Utils::printColorfulMessageNewLine(langManager->getText("EMPTY"),
                                     COLORS::RED);
}

void SystemUI::printAddedVehicle(
    const std::vector<std::unique_ptr<Vehicle>> &vehicles) const {
  for (auto &vehicle : vehicles) {
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

void SystemUI::printTelemetricSimulation(
    const std::unique_ptr<Vehicle> &obj) {
  const std::string_view color{obj->getType() == Vehicle::Type::ElectricVehicle
                                   ? COLORS::BLU
                                   : COLORS::MAGNETA};
  printCarNameInfo(obj->getName(), color, obj->getIsOn(), obj->getFuel());
  printIsRunning(obj->getIsOn());
  printEngineTemp(obj->getEngineTemp(), obj->getWarningTemp(),
                  obj->getDangerTemp());
  printFuel(obj);
  Utils::printNewLine();
}

void SystemUI::printSimulationStartHeader() const {
  Utils::printNewLine();
  Utils::printMessageWithSpace(langManager->getText("TICK_START"));
  Utils::printMessageWithSpace(tickNum++);
  Utils::printMessageNewLine(langManager->getText("TICK_END"));
  Utils::printNewLine();
}

void SystemUI::printCarNameInfo(const std::string_view name,
                                const std::string_view color, const bool &isOn,
                                const double fuel) {
  Utils::printMessageWithSpace(LanguageManager::getText("TELEMETRY"));
  std::cout << color << name << COLORS::RESET << " ";
  if (isOn && fuel > 0) {
    std::cout << LanguageManager::getText("RUN") << ":";
    Utils::printNewLine();
  } else {
    std::cout << LanguageManager::getText("REST") << ":";
    Utils::printNewLine();
  }
}

void SystemUI::printIsRunning(const bool isOn) {
  const std::string_view engine{isOn ? "1.0" : "0.0"};
  const std::string_view color{isOn ? COLORS::GREEN : COLORS::L_YELLOW};
  Utils::printRow(getArrowMsg(LanguageManager::getText("IS_RUN")), engine,
                  color);
}

void SystemUI::printEngineTemp(const double temp, const double warningTemp,
                               const double dangerTemp) {
  const std::string_view color{temp <= warningTemp  ? COLORS::WHITE
                               : temp >= dangerTemp ? COLORS::RED
                                                    : COLORS::L_YELLOW};
  Utils::printRow(getArrowMsg(LanguageManager::getText("E_TEMP")), temp, color);
}

void SystemUI::printFuel(const std::unique_ptr<Vehicle> &obj) {
  const std::string_view color{obj->getFuel() <= obj->getLowFuel() ? COLORS::RED
                               : obj->getFuel() > obj->getMediumFuel() &&
                                       obj->getFuel() <= obj->getMediumFuel()
                                   ? COLORS::L_YELLOW
                               : obj->getFuel() >= obj->getHighFuel()
                                   ? COLORS::GREEN
                                   : COLORS::WHITE};

  Utils::printRow(getArrowMsg(LanguageManager::getText("F_LEVEL")),
                  obj->getFuel(), color);
}

std::string SystemUI::getArrowMsg(const std::string_view msg) {
  const std::string_view arrow{LanguageManager::getText("R_ARROW")};
  return static_cast<std::string>(arrow) + " " + static_cast<std::string>(msg);
}

void SystemUI::printInfo(const std::string_view msg) {
  Utils::printLabel(LanguageManager::getText("INFO"), COLORS::GREEN);
  Utils::printMessageNewLine(msg);
}

void SystemUI::printWarning(const std::string_view msg) {
  Utils::printLabel(LanguageManager::getText("WARNING"), COLORS::YELLOW);
  Utils::printMessageNewLine(msg);
}

void SystemUI::printDanger(const std::string_view msg) {
  Utils::printLabel(LanguageManager::getText("ALERT"), COLORS::RED);
  Utils::printMessageNewLine(msg);
}