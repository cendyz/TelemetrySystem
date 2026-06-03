#pragma once
#include <string>

class Vehicle {
public:
    std::string name;
    double fuel{};
    double enginePower;
    std::string type;
    bool isON{};


    Vehicle(const std::string &name, const double fuel, const double enginePower, const std::string &type)
        : name(std::move(name)), fuel(fuel), enginePower(enginePower), type(std::move(type)) {
    }

    virtual ~Vehicle() = default;
};
