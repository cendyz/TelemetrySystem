#include <Vehicle.h>
#include <random>

std::string_view Vehicle::getName()
{
    return name;
}

double Vehicle::getFuel() const
{
    return fuel;
}

double Vehicle::getEngineTemp() const
{
    return engineTemp;
}

Vehicle::Type Vehicle::getType() const
{
    return type;
}

bool Vehicle::getIsOn() const
{
    return isOn;
}

int Vehicle::getOutOfFuel()
{
    return outOfFuel;
}

int Vehicle::getLowFuel()
{
    return lowFuel;
}

int Vehicle::getMediumFuel()
{
    return mediumFuel;
}

int Vehicle::getHighFuel()
{
    return highFuel;
}

int Vehicle::getWarmedUpEngineTemp()
{
    return warmedUpEngineTemp;
}

int Vehicle::getCooledEngineTemp()
{
    return cooledEngineTemperature;
}

int Vehicle::getWarningTemp() const
{
    return warningTemp;
}

int Vehicle::getDangerTemp() const
{
    return dangerTemp;
}

void Vehicle::updatePhysics()
{
    if (isOn)
    {
        if (engineTemp <= warmedUpEngineTemp)
        {
            warmingUpTheEngine();
        }
        else if (engineTemp >= dangerTemp)
        {
            collingCriticEngineTemp();
        }
        else if (engineTemp >= warmedUpEngineTemp)
        {
            engineTemperatureMaintenance();
        }
    }
    else if (!isOn && engineTemp >= cooledEngineTemperature)
    {
        restingDownTheEngine();
    }

    if (fuel > outOfFuel)
    {
        updateFuel();
    }
}

void Vehicle::isOKToStartVehicle()
{
    if (!isOn && engineTemp < dangerTemp && fuel > outOfFuel)
    {
        isOn = true;
    }
}

double Vehicle::getRandomTemperature()
{
    std::uniform_real_distribution<> dist1(3, 11);
    std::uniform_real_distribution<> dist2(2, 12);
    if (type == Type::ElectricVehicle)
    {
        return dist1(gen);
    }
    return (dist1(gen) + dist2(gen)) / 2;
}

void Vehicle::warmingUpTheEngine()
{
    engineTemp += getRandomTemperature();
}

void Vehicle::restingDownTheEngine()
{
    engineTemp -= getRandomTemperature();
    engineTemp = std::max(engineTemp, 0.0);
}

void Vehicle::engineTemperatureMaintenance()
{
    std::uniform_real_distribution<> newTemp(1, 6);

    if (engineTemp >= warningTemp)
    {
        engineTemp -= newTemp(gen);
        return;
    }

    if (plusMinus == 0)
    {
        if (const double chanceOfCriticalTemperature{newTemp(gen)}; chanceOfCriticalTemperature <= 3)
        {
            engineTemp += newTemp(gen) + 30;
        }
        else
        {
            engineTemp += newTemp(gen);
        }
        plusMinus = 1;
    }
    else
    {
        engineTemp -= newTemp(gen);
        plusMinus = 0;
    }
}

void Vehicle::collingCriticEngineTemp()
{
    std::uniform_real_distribution<> dist(2, 7);

    engineTemp -= dist(gen);
}

void Vehicle::updateFuel()
{
    std::uniform_real_distribution<> dist(0, 2);
    fuel -= dist(gen);

    if (fuel <= outOfFuel)
    {
        fuel = outOfFuel;
        isOn = false;
    }
}
