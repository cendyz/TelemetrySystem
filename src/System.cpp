#include <windows.h>
#include "../include/System.h"
#include "ElectricVehicle.h"
#include "Vehicle.h"
#include <CombustionVehicle.h>
#include <ElectricVehicle.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>

#include "Utils.h"
namespace fs = std::filesystem;

System::System() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
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

    sysUI->printAddedVehicle(vehicles, electricCarType);
    startSimulation();
}

bool System::isVehiclesFileExists() { return fs::exists(vehiclesPath); }

void System::createVehiclesFile() { std::ofstream file(vehiclesPath.data()); }

void System::loadVehiclesFromFile() {
    std::ifstream file{std::string(vehiclesPath)};
    std::string line;

    while (getline(file, line)) {
        readFileLine(line);
    }
}

void System::readFileLine(const std::string &line) {
    std::stringstream ss(line);
    std::string name, enginePower, fuel, type;

    getline(ss, name, ';');
    getline(ss, enginePower, ';');
    getline(ss, fuel, ';');
    getline(ss, type, ';');

    double d_engine{stod(enginePower)};
    double d_fuel(stod(fuel));

    std::unique_ptr<Vehicle> newVehicle;

    if (type == electricCarType) {
        newVehicle = std::make_unique<ElectricVehicle>(std::move(name), d_engine,
                                                       d_fuel, std::move(type));
    } else {
        newVehicle = std::make_unique<CombustionVehicle>(std::move(name), d_engine,
                                                         d_fuel, std::move(type));
    }

    addVehicleToVar(std::move(newVehicle));
}

void System::addVehicleToVar(std::unique_ptr<Vehicle> vehicle) {
    if (vehicle) {
        vehicles.emplace_back(std::move(vehicle));
    }
}

void System::startSimulation() {
    std::cout << "\033[?25l";
    std::cout << "\033[s";

    while (true) {
        std::cout << "\033[u\033[J";
        for (auto &vehicle : vehicles) {
            sysUI->printTelemetricSimulation(vehicle);
        }
        std::cout.flush();

        Utils::pauseOutputForSec();
    }
    std::cout << '\n';
}
