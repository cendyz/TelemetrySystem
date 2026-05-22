#pragma once
#include "Vehicle.h"
#include <string>

class Car : public Vehicle {
public:
    Car() = default;
    explicit Car(const std::string_view name) : carName{name} {}

    [[nodiscard]] bool startEngine();
    [[nodiscard]] bool stopEngine();

private:
    std::string_view carName;
    double carTemperature{};
};