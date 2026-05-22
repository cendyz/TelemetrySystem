#pragma once

#include <unordered_map>
#include <string>

class Vehicle {
public:
    Vehicle() = default;
    virtual ~Vehicle() = default;

    virtual bool start() = 0;
    virtual bool stop() = 0;

    virtual void setSpeed(float speed_kmh) = 0;
    virtual void setSteeringAngle(float degrees) = 0;

    [[nodiscard]] virtual std::unordered_map<std::string, double> getTelemetry() const = 0;
};