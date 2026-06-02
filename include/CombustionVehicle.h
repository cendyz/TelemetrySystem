#pragma once
#include "Vehicle.h"

class CombustionVehicle : public Vehicle {
public:
  using Vehicle::Vehicle;
  ~CombustionVehicle() override = default;
};
