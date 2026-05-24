#pragma once

#include <iostream>

class Vehicle {
public:
    Vehicle() = default;
    virtual ~Vehicle() = default;

    virtual void start() = 0;
    virtual void turnOff() = 0;
    static void makeNoise() {
        std::cout << "brum brum" << '\n';
    }
};