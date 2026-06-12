#include "../include/System.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include "ElectricVehicle.h"
#include "Vehicle.h"
#include <CombustionVehicle.h>
#include <ElectricVehicle.h>
#include <random>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>
#include <csignal>
#include "Utils.h"
namespace fs = std::filesystem;

constexpr std::string_view getOSname() {
#if defined(_WIN32)
    return "windows";
#else
    return "linux";
#endif
}

System::System() {
    if (getOSname() == "windows") {
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    }
}

void System::run() {
    sysUI = std::make_unique<SystemUI>();
    sysUI->printInitializationMessages();

    if (!isVehiclesFileExists()) {
        createVehiclesFile();
    }

    loadVehiclesFromFile();

    if (vehicles.empty()) {
        sysUI->printVehiclesFileIsEmpty();
        return;
    }

    sysUI->printAddedVehicle(vehicles);
    startSimulation();
}

bool System::isVehiclesFileExists() const { return fs::exists(vehiclesPath); }

void System::createVehiclesFile() const { std::ofstream file(vehiclesPath); }

void System::loadVehiclesFromFile() {
    std::ifstream file{vehiclesPath};
    std::string line;

    while (getline(file, line)) {
        readFileLine(line);
    }
}

void System::readFileLine(const std::string &line) {
    std::stringstream ss(line);
    std::string name, fuel, type;

    getline(ss, name, ';');
    getline(ss, fuel, ';');
    getline(ss, type, ';');

    const double d_fuel(stod(fuel));
    const int i_type{stoi(type)};

    std::unique_ptr<Vehicle> newVehicle;

    if (static_cast<Vehicle::Type>(i_type) == Vehicle::Type::ElectricVehicle) {
        newVehicle = std::make_unique<ElectricVehicle>(std::move(name), d_fuel);
    } else {
        newVehicle = std::make_unique<CombustionVehicle>(std::move(name), d_fuel);
    }

    addVehicleToVar(std::move(newVehicle));
}

void System::addVehicleToVar(std::unique_ptr<Vehicle> vehicle) {
    if (vehicle) {
        vehicles.emplace_back(std::move(vehicle));
    }
}

void System::startSimulation() const {
    signal(SIGINT, handleExit);

    hideAndSaveCursorPosition();

    while (true) {
        cursorBackAndCleaningBottom();
        sysUI->printSimulationStartHeader();
        std::uint8_t isAllOK{1};

        for (auto &vehicle: vehicles) {
            sysUI->printTelemetricSimulation(vehicle);
            vehicle->isOKToStartVehicle();

            if (vehicle->getEngineTemp() >= vehicle->getDangerTemp()) {
                --isAllOK;
                sysUI->printEngineDanger();
            } else if (vehicle->getEngineTemp() >= vehicle->getWarningTemp()) {
                --isAllOK;
                sysUI->printEngineWarning();
            }

            if (vehicle->getFuel() <= vehicle->getOutOfFuel()) {
                --isAllOK;
                sysUI->printNoFuel();
            } else if (vehicle->getFuel() <= vehicle->getLowFuel()) {
                --isAllOK;
                sysUI->printLowFuelLevel();
            } else if (vehicle->getFuel() == vehicle->getOutOfFuel() || vehicle->getFuel() <= vehicle->
                       getMediumFuel()) {
                --isAllOK;
                sysUI->printMediumFuelLevel();
            }

            if (isAllOK == 1) {
                sysUI->pritnAllOkInfo();
            }
            isAllOK = 1;
            Utils::printNewLine();

            vehicle->updatePhysics();
        }

        std::cout.flush();
        Utils::pauseOutputForXSec(2);
    }
}

void System::handleExit(const int signum) {
    std::cout << "\033[?25h";
    exit(signum);
}

void System::hideAndSaveCursorPosition() {
    std::cout << "\033[?25l";
    std::cout << "\033[s";
}

void System::cursorBackAndCleaningBottom() {
    std::cout << "\033[u\033[J";
}
