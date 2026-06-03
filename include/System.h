#pragma once
#include <windows.h>
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
    std::vector<std::unique_ptr<Vehicle> > vehicles;

    static constexpr std::string_view vehiclesPath{"../../data/vehicles.csv"};

    [[nodiscard]] static bool isVehiclesFileExists();

    static void createVehiclesFile();

    void loadVehiclesFromFile();

    void readFileLine(const std::string &line);

    static constexpr std::string_view electricCarType{"electric"};

    void addVehicleToVar(std::unique_ptr<Vehicle> vehicle);

    void startSimulation();
};
