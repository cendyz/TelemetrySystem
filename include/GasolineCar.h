#pragma once
#include "Vehicle.h"

class GasolineCar : public Vehicle {
public:
    void start() override;
    void turnOff() override;
};