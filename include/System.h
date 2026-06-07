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
    std::vector<std::unique_ptr<Vehicle> > vehicles;

    std::string vehiclesPath{"../data/vehicles.csv"};

    [[nodiscard]] bool isVehiclesFileExists() const;

    void createVehiclesFile() const;

    void loadVehiclesFromFile();

    void readFileLine(const std::string &line);

    void addVehicleToVar(std::unique_ptr<Vehicle> vehicle);

    void startSimulation();

    static void handleExit(int signum);

    static void hideAndSaveCursorPosition();

    [[nodiscard]] bool isOKToStartVehicle(double engTemp, bool &engIsOn);
};
