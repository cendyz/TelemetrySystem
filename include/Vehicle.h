#pragma once
#include <string>

class Vehicle {
public:
    enum class Type {
        CombustionVehicle = 1,
        ElectricVehicle = 2
    };


    Vehicle(std::string name, const double fuel, const Type type)
        : name(std::move(name)), fuel(fuel), type(type) {
    }

    void isOKToStartVehicle();

    virtual void updatePhysics();

    virtual ~Vehicle() = default;

    [[nodiscard]] std::string_view getName() const;

    [[nodiscard]] double getFuel() const;

    [[nodiscard]] double getEngineTemp() const;

    [[nodiscard]] Type getType() const;

    [[nodiscard]] bool getIsOn() const;

    [[nodiscard]] int getOutOfFuel();

    [[nodiscard]] int getLowFuel();

    [[nodiscard]] int getMediumFuel();

    [[nodiscard]] int getHighFuel();

    [[nodiscard]] int getWarmedUpEngineTemp() const;

    [[nodiscard]] int getCooledEnginteTemp() const;

    [[nodiscard]] int getWarningTemp() const;

    [[nodiscard]] int getDangerTemp() const;

protected:
    double warningTemp{};
    double dangerTemp{};

private:
    std::string name;
    double fuel{};
    double engineTemp{};
    Type type;
    bool isOn{};
    const int outOfFuel{};
    const int lowFuel{20};
    const int mediumFuel{50};
    const int highFuel{80};
    const int warmedUpEngineTemp{80};
    double cooledEngineTemperature{};

    void warmingUpTheEngine();

    [[nodiscard]] double getRandomTemperature() const;

    void collingCriticEngineTemp();

    void engineTemperatureMaintenance();

    void restingDownTheEngine();

    void updateFuel();
};
