#pragma once
#include "Vehicle.h"


class CombustionVehicle : public Vehicle {
  public:
      // CombustionVehicle(const std::string & name, double enginePower, double fuel) : Vehicle(name, enginePower, fuel) {}
      using Vehicle::Vehicle;
      ~CombustionVehicle() override = default;
};