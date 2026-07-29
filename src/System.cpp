#include "../include/System.h"
#include "Colors.h"
#include "ElectricVehicle.h"
#include "LanguageManager.h"
#include "SystemUI.h"
#include "Utils.h"
#include "Vehicle.h"
#include <CombustionVehicle.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <windows.h>

System::System()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void System::run()
{
    LanguageManager::setLanguage();
    LanguageManager::loadDict();
    hideCursorPosition();
    SystemUI::printInitializationMessages(LanguageManager::getSystemsInfo(), LanguageManager::getInitsInfo());

    if (!isVehiclesFileExists())
    {
        createVehiclesFile();
    }

    loadVehiclesFromFile();

    if (vehicles.empty())
    {
        SystemUI::printVehiclesFileIsEmpty();
        return;
    }

    SystemUI::printAddedVehicle(vehicles);
    startSimulation();
}

bool System::isVehiclesFileExists() const
{
    return std::filesystem::exists(vehiclesPath);
}

void System::createVehiclesFile() const
{
    std::ofstream file(vehiclesPath);
}

void System::loadVehiclesFromFile()
{
    std::ifstream file{vehiclesPath};
    std::string line;

    while (getline(file, line))
    {
        readFileLine(line);
    }
}

void System::readFileLine(const std::string& line)
{
    std::stringstream ss(line);
    std::string name, fuel, type;

    getline(ss, name, ';');
    getline(ss, fuel, ';');
    getline(ss, type, ';');

    const double d_fuel(stod(fuel));
    const int i_type{stoi(type)};

    std::unique_ptr<Vehicle> newVehicle;

    if (static_cast<Vehicle::Type>(i_type) == Vehicle::Type::ElectricVehicle)
    {
        newVehicle = std::make_unique<ElectricVehicle>(std::move(name), d_fuel);
    }
    else
    {
        newVehicle = std::make_unique<CombustionVehicle>(std::move(name), d_fuel);
    }

    addVehicleToVar(std::move(newVehicle));
}

void System::addVehicleToVar(std::unique_ptr<Vehicle> vehicle)
{
    if (vehicle)
    {
        vehicles.emplace_back(std::move(vehicle));
    }
}

void System::startSimulation() const
{
    signal(SIGINT, handleExit);

    saveCursorPosition();

    while (Utils::interrupted == 0)
    {
        cursorBackAndCleaningBottom();
        SystemUI::printSimulationStartHeader();
        std::uint8_t isAllOK{1};

        for (const auto& vehicle : vehicles)
        {
            SystemUI::printTelemetricSimulation(vehicle);
            vehicle->isOKToStartVehicle();

            if (vehicle->getEngineTemp() >= vehicle->getDangerTemp())
            {
                --isAllOK;
                SystemUI::printDanger();
            }
            else if (vehicle->getEngineTemp() >= vehicle->getWarningTemp())
            {
                --isAllOK;
                SystemUI::printWarning(LanguageManager::getText("WARNING_TEMP"));
            }

            if (vehicle->getFuel() <= Vehicle::getOutOfFuel())
            {
                --isAllOK;
                SystemUI::printInfo();
            }
            else if (vehicle->getFuel() <= Vehicle::getLowFuel())
            {
                --isAllOK;
                SystemUI::printWarning(LanguageManager::getText("ALERT"));
            }
            else if (vehicle->getFuel() == Vehicle::getOutOfFuel() || vehicle->getFuel() <= Vehicle::getMediumFuel())
            {
                --isAllOK;
                SystemUI::printWarning(LanguageManager::getText("MEDIUM_FUEL"));
            }

            if (isAllOK == 1)
            {
                SystemUI::printInfo();
            }
            isAllOK = 1;
            Utils::printNewLine();

            vehicle->updatePhysics();
        }

        std::cout.flush();
        Utils::pauseOutputForOneSec();
    }
    std::cout << "\033[?25h";
    exit(0);
}

void System::handleExit(const int signum)
{
    Utils::interrupted = 1;
}

void System::hideCursorPosition()
{
    std::cout << "\033[?25l";
}

void System::saveCursorPosition()
{
    std::cout << "\033[s";
}

void System::cursorBackAndCleaningBottom()
{
    std::cout << "\033[u\033[J";
}
