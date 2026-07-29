#pragma once
#include "Vehicle.h"
#include <filesystem>
#include <memory>
#include <vector>

class System
{
  public:
    System();
    void run();

  private:
    std::vector<std::unique_ptr<Vehicle>> vehicles;

    const std::filesystem::path vehiclesPath{DATA_DIR "vehicles.csv"};

    [[nodiscard]] bool isVehiclesFileExists() const;

    void createVehiclesFile() const;

    void loadVehiclesFromFile();

    void readFileLine(const std::string& line);

    void addVehicleToVar(std::unique_ptr<Vehicle> vehicle);

    void startSimulation() const;

    static void handleExit(int signum);

    static void cursorBackAndCleaningBottom();

    static void hideCursorPosition();

    static void saveCursorPosition();
};
