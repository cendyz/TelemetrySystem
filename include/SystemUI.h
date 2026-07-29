#pragma once
#include "Vehicle.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

class SystemUI
{
  public:
    static void printInitializationMessages(const std::array<std::string, 2>& systems,
                                            const std::array<std::string, 2>& inits);

    static void printVehiclesFileIsEmpty();

    static void printAddedVehicle(const std::vector<std::unique_ptr<Vehicle>>& vehicles);

    static void printTelemetricSimulation(const std::unique_ptr<Vehicle>& obj);

    void printSimulationStartHeader();

    static void printInfo();

    static void printWarning(std::string_view msg);

    static void printDanger();

  private:
    int tickNum{1};

    static void printCarNameInfo(std::string_view name, std::string_view color, const bool& isOn, double fuel);

    static void printIsRunning(bool isOn);

    [[nodiscard]] static std::string getArrowMsg(std::string_view msg);

    static void printEngineTemp(double temp, double warningTemp, double dangerTemp);

    static void printFuel(const std::unique_ptr<Vehicle>& obj);
};
