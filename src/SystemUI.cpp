#include "../include/SystemUI.h"
#include "../include/Utils.h"
#include "Colors.h"
#include "LanguageManager.h"
#include <iostream>
#include <memory>

void SystemUI::printInitializationMessages(const std::array<std::string, 2>& systems,
                                           const std::array<std::string, 2>& inits)
{
    for (size_t i{}; i < systems.size(); ++i)
    {
        Utils::printLabel(LanguageManager::getText(systems[i]), COLORS::YELLOW);
        Utils::printMessageNewLine(LanguageManager::getText(inits[i]));
        Utils::pauseOutputForOneSec();
    }
}

void SystemUI::printVehiclesFileIsEmpty()
{
    Utils::printColorfulMessageNewLine(LanguageManager::getText("EMPTY"), COLORS::RED);
}

void SystemUI::printAddedVehicle(const std::vector<std::unique_ptr<Vehicle>>& vehicles)
{
    for (const auto& vehicle : vehicles)
    {
        Utils::printLabel(LanguageManager::getText("S_INFO"), COLORS::YELLOW);
        if (vehicle->getType() != Vehicle::Type::ElectricVehicle)
        {
            Utils::printMessageWithSpace(LanguageManager::getText("ADD_COMBUSTION"));
            Utils::printColorfulMessageNewLine(vehicle->getName(), COLORS::BLU);
        }
        else
        {
            Utils::printMessageWithSpace(LanguageManager::getText("ADD_ELECTRIC"));
            Utils::printColorfulMessageNewLine(vehicle->getName(), COLORS::MAGNETA);
        }

        Utils::pauseOutputForOneSec();
    }
}

void SystemUI::printTelemetricSimulation(const std::unique_ptr<Vehicle>& obj)
{
    const std::string_view color{obj->getType() == Vehicle::Type::ElectricVehicle ? COLORS::BLU : COLORS::MAGNETA};
    printCarNameInfo(obj->getName(), color, obj->getIsOn(), obj->getFuel());
    printIsRunning(obj->getIsOn());
    printEngineTemp(obj->getEngineTemp(), obj->getWarningTemp(), obj->getDangerTemp());
    printFuel(obj);
    Utils::printNewLine();
}

void SystemUI::printSimulationStartHeader()
{
    Utils::printNewLine();
    Utils::printMessageWithSpace(LanguageManager::getText("TICK_START"));
    Utils::printMessageWithSpace(tickNum++);
    Utils::printMessageNewLine(LanguageManager::getText("TICK_END"));
    Utils::printNewLine();
}

void SystemUI::printCarNameInfo(const std::string_view name, const std::string_view color, const bool& isOn,
                                const double fuel)
{
    Utils::printMessageWithSpace(LanguageManager::getText("TELEMETRY"));
    std::cout << color << name << COLORS::RESET << " ";
    if (isOn && fuel > 0)
    {
        std::cout << LanguageManager::getText("RUN") << ":";
        Utils::printNewLine();
    }
    else
    {
        std::cout << LanguageManager::getText("REST") << ":";
        Utils::printNewLine();
    }
}

void SystemUI::printIsRunning(const bool isOn)
{
    const std::string_view engine{isOn ? "1.0" : "0.0"};
    const std::string_view color{isOn ? COLORS::GREEN : COLORS::L_YELLOW};
    Utils::printRow(getArrowMsg(LanguageManager::getText("IS_RUN")), engine, color);
}

void SystemUI::printEngineTemp(const double temp, const double warningTemp, const double dangerTemp)
{
    std::string_view color{COLORS::L_YELLOW};
    if (temp <= warningTemp)
    {
        color = COLORS::WHITE;
    }
    else if (temp >= dangerTemp)
    {
        color = COLORS::RED;
    }

    Utils::printRow(getArrowMsg(LanguageManager::getText("E_TEMP")), temp, color);
}

void SystemUI::printFuel(const std::unique_ptr<Vehicle>& obj)
{
    std::string_view color{COLORS::WHITE};
    if (obj->getFuel() <= Vehicle::getLowFuel())
    {
        color = COLORS::RED;
    }
    else if (obj->getFuel() > Vehicle::getLowFuel() && obj->getFuel() <= Vehicle::getMediumFuel())
    {
        color = COLORS::L_YELLOW;
    }
    else if (obj->getFuel() >= Vehicle::getHighFuel())
    {
        color = COLORS::GREEN;
    }

    Utils::printRow(getArrowMsg(LanguageManager::getText("F_LEVEL")), obj->getFuel(), color);
}

std::string SystemUI::getArrowMsg(const std::string_view msg)
{
    const std::string_view arrow{LanguageManager::getText("R_ARROW")};
    return static_cast<std::string>(arrow) + " " + static_cast<std::string>(msg);
}

void SystemUI::printInfo()
{
    Utils::printLabel(LanguageManager::getText("INFO"), COLORS::GREEN);
    Utils::printMessageNewLine(LanguageManager::getText("FINE"));
}

void SystemUI::printWarning(const std::string_view msg)
{
    Utils::printLabel(LanguageManager::getText("WARNING"), COLORS::YELLOW);
    Utils::printMessageNewLine(msg);
}

void SystemUI::printDanger()
{
    Utils::printLabel(LanguageManager::getText("ALERT"), COLORS::RED);
    Utils::printMessageNewLine(LanguageManager::getText("DANGER_TEMP"));
}