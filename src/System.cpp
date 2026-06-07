#include "../include/System.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include "ElectricVehicle.h"
#include "Vehicle.h"
#include <CombustionVehicle.h>
#include <ElectricVehicle.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>
#include <csignal>
#include "Utils.h"
namespace fs = std::filesystem;

System::System() {
    Utils::checkOS(vehiclesPath);
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

    sysUI->printAddedVehicle(vehicles, SystemUI::electricCarType);
    startSimulation();
}

bool System::isVehiclesFileExists() const { return fs::exists(vehiclesPath); }

void System::createVehiclesFile() const { std::ofstream file(vehiclesPath); }

void System::loadVehiclesFromFile() {
    std::ifstream file{std::string(vehiclesPath)};
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

    std::unique_ptr<Vehicle> newVehicle;

    if (type == SystemUI::electricCarType) {
        newVehicle = std::make_unique<ElectricVehicle>(std::move(name), d_fuel, std::move(type));
    } else {
        newVehicle = std::make_unique<CombustionVehicle>(std::move(name), d_fuel, std::move(type));
    }

    addVehicleToVar(std::move(newVehicle));
}

void System::addVehicleToVar(std::unique_ptr<Vehicle> vehicle) {
    if (vehicle) {
        vehicles.emplace_back(std::move(vehicle));
    }
}

void System::startSimulation() {
    signal(SIGINT, handleExit);

    hideAndSaveCursorPosition();

    while (true) {
        std::cout << "\033[u\033[J";
        std::cout << '\n';
        sysUI->printSimulationStartHeader();
        for (auto &vehicle: vehicles) {
            sysUI->printTelemetricSimulation(vehicle);
        }
        std::cout.flush();
        Utils::pauseOutputForXSec(3);
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

bool System::isOKToStartVehicle(const double engTemp, bool &engIsOn) {
    if (engTemp > sysUI->dangerEngTemp) {
        if (engIsOn) {
            engIsOn = false;
            sysUI->printEngineWarning();
        }
    }
}
