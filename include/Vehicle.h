#pragma once
#include <string>

class Vehicle {
public:
    enum class Type {
        CombustionVehicle = 1,
        ElectricVehicle = 2
    };

    std::string name;
    double fuel{};
    double engineTemp{};
    Type type;
    bool isON{};
    double outOfFuel{};
    double warmedUpEngineTemp{80};
    double cooledEngineTemperature{};
    double warningTemp{};
    double dangerTemp{};


    Vehicle(std::string name, const double fuel, const Type type)
        : name(std::move(name)), fuel(fuel), type(type) {
    }

    virtual void updatePhysics();

    virtual ~Vehicle() = default;

private:
    virtual void isOKToStartVehicle() = 0;

    virtual void warmingUpTheEngine() = 0;

    virtual void collingCriticEngineTemp() = 0;

    virtual void engineTemperatureMaintenance() = 0;

    virtual void restingDownTheEngine() = 0;

    virtual void updateFuel() = 0;
};
