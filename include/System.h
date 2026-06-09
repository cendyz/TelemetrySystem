#pragma once
#include "SystemUI.h"
#include "Vehicle.h"
#include <memory>
#include <vector>
#include <filesystem>

class System {
public:
    System();

    void run();

private:
    std::unique_ptr<SystemUI> sysUI;
    std::vector<std::unique_ptr<Vehicle> > vehicles;

    const std::filesystem::path vehiclesPath{"../data/vehicles.csv"};

    [[nodiscard]] bool isVehiclesFileExists() const;

    void createVehiclesFile() const;

    void loadVehiclesFromFile();

    void readFileLine(const std::string &line);

    void addVehicleToVar(std::unique_ptr<Vehicle> vehicle);

    void startSimulation() const;

    static void handleExit(int signum);

    static void hideAndSaveCursorPosition();

    static void isOKToStartVehicle(double engTemp, bool &engIsOn, double fuel);

    [[nodiscard]] static double warmingRestingNumGenerator(const std::string &type);

    static void warmingUpTheEngine(double &engTemp, const std::string &type);

    static void restingDownTheEngine(double &engTemp, const std::string &type);

    static void updateFuel(double &fuel, bool &engineIsOn);

    static void engineTemperatureMaintenance(double &engTemp);

    static void collingCriticEngineTemp(double &engTemp);
};
