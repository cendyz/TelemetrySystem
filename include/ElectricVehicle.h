#pragma once
#include "Vehicle.h"

class ElectricVehicle : public Vehicle {
public:
  using Vehicle::Vehicle;
  ~ElectricVehicle() override = default;
};
