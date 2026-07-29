#pragma once
#include <random>
#include <string>

class Vehicle
{
  public:
    enum class Type : std::uint8_t
    {
        CombustionVehicle = 1,
        ElectricVehicle = 2
    };

    Vehicle(std::string name, const double fuel, const Type type)
        : name(std::move(name)), fuel(fuel), type(type), gen(std::random_device{}())
    {
    }

    void isOKToStartVehicle();

    void updatePhysics();

    virtual ~Vehicle() = default;

    [[nodiscard]] std::string_view getName() ;

    [[nodiscard]] double getFuel() const ;

    [[nodiscard]] double getEngineTemp() const ;

    [[nodiscard]] Type getType() const;

    [[nodiscard]] bool getIsOn() const ;

    [[nodiscard]] static int getOutOfFuel();

    [[nodiscard]] int static getLowFuel();

    [[nodiscard]] int static getMediumFuel();

    [[nodiscard]] static int getHighFuel();

    [[nodiscard]] static int getWarmedUpEngineTemp();

    [[nodiscard]] static int getCooledEngineTemp();

    [[nodiscard]] int getWarningTemp() const ;

    [[nodiscard]] int getDangerTemp() const ;

  protected:
    int warningTemp{};
    int dangerTemp{};

  private:
    std::string name;
    double fuel{};
    double engineTemp{};
    Type type;
    bool isOn{};
    static constexpr int outOfFuel{};
    static constexpr int lowFuel{20};
    static constexpr int mediumFuel{50};
    static constexpr int highFuel{80};
    static constexpr int warmedUpEngineTemp{80};
    static constexpr int cooledEngineTemperature{};

    std::uint8_t plusMinus{};
    std::mt19937 gen;

    void warmingUpTheEngine();

    [[nodiscard]] double getRandomTemperature();

    void collingCriticEngineTemp();

    void engineTemperatureMaintenance();

    void restingDownTheEngine();

    void updateFuel();
};
