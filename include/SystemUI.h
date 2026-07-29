#pragma once
#include "Vehicle.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace SystemUI
{
void printInitializationMessages(const std::array<std::string, 2>& systems, const std::array<std::string, 2>& inits);

void printVehiclesFileIsEmpty();

void printAddedVehicle(const std::vector<std::unique_ptr<Vehicle>>& vehicles);

void printTelemetricSimulation(const std::unique_ptr<Vehicle>& obj);

void printSimulationStartHeader();

void printInfo();

void printWarning(std::string_view msg);

void printDanger();

inline int tickNum{1};

[[nodiscard]] std::string_view pickColorForThreshold(double val, int low, int medium, int high);

void printCarNameInfo(std::string_view name, std::string_view color, const bool& isOn, double fuel);

void printIsRunning(bool isOn);

[[nodiscard]] std::string getArrowMsg(std::string_view msg);

void printEngineTemp(double temp, double warningTemp, double dangerTemp);

void printFuel(const std::unique_ptr<Vehicle>& obj);

}; // namespace SystemUI
