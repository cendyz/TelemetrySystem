#pragma once
#include "Vehicle.h"

class ElectricVehicle : public Vehicle {
public:
    ElectricVehicle(std::string name, const double fuel) : Vehicle(std::move(name),
                                                                   fuel, Type::ElectricVehicle) {
        warningTemp = 100;
        dangerTemp = 115;
    }

    ~ElectricVehicle() override = default;
};
