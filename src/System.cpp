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

    sysUI->printAddedVehicle(vehicles, SystemUI::electricCarType);
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
            isOKToStartVehicle(vehicle->engineTemp, vehicle->isON, vehicle->fuel);

            if (vehicle->engineTemp >= SystemUI::dangerEngTemp) {
                --isAllOK;
                sysUI->printEngineDanger();
            } else if (vehicle->engineTemp >= SystemUI::warningEngTemp) {
                --isAllOK;
                sysUI->printEngineWarning();
            }

            if (vehicle->fuel <= SystemUI::outOfFuel) {
                --isAllOK;
                sysUI->printNoFuel();
            } else if (vehicle->fuel <= SystemUI::lowFuel) {
                --isAllOK;
                sysUI->printLowFuelLevel(vehicle->type);
            } else if (vehicle->fuel == SystemUI::outOfFuel || vehicle->fuel <= SystemUI::mediumFuel) {
                --isAllOK;
                sysUI->printMediumFuelLevel();
            }



            if (isAllOK == 1) {
                sysUI->pritnAllOkInfo();
            }
            isAllOK = 1;
            Utils::printNewLine();
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

void System::isOKToStartVehicle(const double engTemp, bool &engIsOn, const double fuel) {
    if (!engIsOn && engTemp < SystemUI::dangerEngTemp && fuel > SystemUI::outOfFuel) {
        engIsOn = true;
    }
}

double System::getRandomTemperature(const std::string &type) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist1(3, 18);
    std::uniform_real_distribution<> dist2(2, 13);
    if (type == SystemUI::electricCarType) {
        return dist1(gen);
    }
    return (dist1(gen) + dist2(gen)) / 2;
}

void System::warmingUpTheEngine(double &engTemp, const std::string &type) {
    engTemp += getRandomTemperature(type);
}

void System::restingDownTheEngine(double &engTemp, const std::string &type) {
    engTemp -= getRandomTemperature(type);

    if (engTemp <= SystemUI::cooledEngineTemperature) {
        engTemp = SystemUI::cooledEngineTemperature;
    }
}

void System::engineTemperatureMaintenance(double &engTemp) {
    static std::uint8_t plusMinus{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> newTemp(1, 7);

    const double chanceOfCriticalTemperature{newTemp(gen)};

    if (engTemp >= SystemUI::warningEngTemp) {
        plusMinus = 1;
    }

    if (!plusMinus) {
        if (chanceOfCriticalTemperature <= 2) {
            engTemp += newTemp(gen) + 30;
        } else {
            engTemp += newTemp(gen);
        }
        plusMinus = 1;
    } else {
        engTemp -= newTemp(gen);
        plusMinus = 0;
    }
}

void System::collingCriticEngineTemp(double &engTemp) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(5, 15);

    engTemp -= dist(gen);
}

void System::updateFuel(double &fuel, bool &engineIsOn) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 2);
    fuel -= dist(gen);

    if (fuel <= SystemUI::outOfFuel) {
        fuel = SystemUI::outOfFuel;
        engineIsOn = false;
    }
}
