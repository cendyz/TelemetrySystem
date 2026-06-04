#pragma once
#include <string>

class Vehicle {
public:
    std::string name;
    double fuel{};
    double engineTemp{};
    std::string type;
    bool isON{};


    Vehicle(std::string name, const double fuel, std::string type)
        : name(std::move(name)), fuel(fuel), type(std::move(type)) {
    }

    virtual ~Vehicle() = default;
};
