#pragma once
#include "Vehicle.h"

class CombustionVehicle : public Vehicle {
public:
    CombustionVehicle(std::string name, const double fuel) : Vehicle(std::move(name), fuel, Type::CombustionVehicle) {
        warningTemp = 105;
        dangerTemp = 120;
    }

    ~CombustionVehicle() override = default;
};
