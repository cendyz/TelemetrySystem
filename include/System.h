#pragma once
#include "SystemUI.h"
#include "Vehicle.h"
#include <memory>
#include <vector>

class System {
public:
    System();
    void run();

private:
    std::unique_ptr<SystemUI> sysUI;
    std::vector<Vehicle> vehicles;

    inline static const std::string vehiclesPath{"../data/vehicles.csv"};
    [[nodiscard]] bool isVehiclesFileExists();
    void createVehiclesFile();
    
    void loadVehiclesFromFile();
    void readFileLine(const std::string &line);
    void addVehicleToVar(Vehicle &obj);
};
