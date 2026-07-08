#pragma once
#include "Vehicle.h"
#include "SystemUI.h"
#include <filesystem>
#include <memory>
#include <vector>

class System {
public:
  System();

  void run() ;

private:
    std::unique_ptr<SystemUI> sysUI{nullptr};
  inline static std::vector<std::unique_ptr<Vehicle>> vehicles;

  inline static const std::filesystem::path vehiclesPath{DATA_DIR
                                                         "vehicles.csv"};

  [[nodiscard]] static bool isVehiclesFileExists();

  static void createVehiclesFile();

  inline static void loadVehiclesFromFile();

  inline static void readFileLine(const std::string &line);

  inline static void addVehicleToVar(std::unique_ptr<Vehicle> vehicle);

  static void startSimulation() ;

  inline static void handleExit(int signum);

  inline static void cursorBackAndCleaningBottom();

  inline static void hideCursorPosition();

  inline static void saveCursorPosition();
};
