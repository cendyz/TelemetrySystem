#include "../include/System.h"
#include "ElectricVehicle.h"
#include "Vehicle.h"
#include <CombustionVehicle.h>
#include <ElectricVehicle.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
namespace fs = std::filesystem;

System::System() { run(); }

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
}

bool System::isVehiclesFileExists() { return fs::exists(vehiclesPath); }

void System::createVehiclesFile() { std::ofstream file(vehiclesPath); }

void System::loadVehiclesFromFile() {
  std::ifstream file{vehiclesPath};
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

  std::vector<std::string> vehicle{std::move(name), std::move(enginePower),
                                   std::move(fuel), std::move(type)};
  addVehicleToVar(vehicle);
}

void System::addVehicleToVar(const std::vector<std::string> &vehicle) {
  std::unique_ptr<Vehicle> newVehicle;
  double dEp{stod(vehicle[static_cast<int>(Info::EngineP)])};
  double dF{stod(vehicle[static_cast<int>(Info::Fuel)])};

  if (vehicle[static_cast<int>(Info::Type)] == electricCarType) {
    newVehicle = std::make_unique<CombustionVehicle>(std::move(vehicle[static_cast<int>(Info::Name)]), dEp,
                                            dF, std::move(vehicle[static_cast<int>(Info::Type)]));
  } else {
    newVehicle = std::make_unique<ElectricVehicle>(std::move(vehicle[static_cast<int>(Info::Name)]), dEp,
                                        dF, std::move(vehicle[static_cast<int>(Info::Type)]));
  }

  vehicles.emplace_back(std::move(newVehicle));
}
