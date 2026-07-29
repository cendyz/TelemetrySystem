#pragma once
#include "LanguageManager.h"
#include "SystemUI.h"
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
    std::unique_ptr<LanguageManager> lngManager{nullptr};
    std::unique_ptr<SystemUI> sysUI{nullptr};
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
