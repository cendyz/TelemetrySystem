#pragma once
#include "Vehicle.h"

class ElectricVehicle : public Vehicle {
public:
    ElectricVehicle(std::string name, const double fuel) : Vehicle(std::move(name),
                                                                   fuel, Type::ElectricVehicle) {
        warningTemp = 90;
        dangerTemp = 110;
    }

    ~ElectricVehicle() override = default;
};
