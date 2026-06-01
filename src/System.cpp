#include "../include/System.h"
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <CombustionVehicle.h>
namespace fs = std::filesystem;

System::System() { run(); }

void System::run() {
  sysUI = std::make_unique<SystemUI>();
  sysUI->printInitializationMessages();

  if (!isVehiclesFileExists()) {
    createVehiclesFile();
    sysUI->printVehiclesFileIsEmpty();
    return;
  }
}

bool System::isVehiclesFileExists() { return fs::exists(vehiclesPath); }

void System::createVehiclesFile() { std::ofstream file(vehiclesPath); }

void System::loadVehiclesFromFile() {
    std::ifstream file{vehiclesPath};
    std::string line;
    
    while(getline(file, line)) {
        readFileLine(line);
    }
}

void System::readFileLine(const std::string &line) {
    std::stringstream ss(line);
    std::string name, enginePower, fuel;
    std::unique_ptr<Vehicle> combustion;
    std::unique_ptr<Vehicle> gasoline;

    getline(ss, name, ';');
    getline(ss, enginePower, ';');
    getline(ss, fuel, ';');

    double dF{stod(fuel)};
    double dEp{stod(enginePower)};

    if(name.find("XV")) {
        combustion = std::make_unique<CombustionVehicle>(name, dEp, dF);
    } else {
        gasoline = std::make_unique<Ga()
    }
    
}
