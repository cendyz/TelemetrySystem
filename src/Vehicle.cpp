#include <Vehicle.h>
#include <random>

std::string_view Vehicle::getName() const {
    return name;
}

double Vehicle::getFuel() const {
    return fuel;
}

double Vehicle::getEngineTemp() const {
    return engineTemp;
}

Vehicle::Type Vehicle::getType() const {
    return type;
}

bool Vehicle::getIsOn() const {
    return isOn;
}

int Vehicle::getOutOfFuel() {
    return outOfFuel;
}
int Vehicle::getLowFuel() {
    return lowFuel;
}

int Vehicle::getMediumFuel() {
    return mediumFuel;
}

int Vehicle::getHighFuel() {
    return highFuel;
}

int Vehicle::getWarmedUpEngineTemp() const {
    return warmedUpEngineTemp;
}

int Vehicle::getCooledEnginteTemp() const {
    return cooledEngineTemperature;
}

int Vehicle::getWarningTemp() const {
    return warningTemp;
}

int Vehicle::getDangerTemp() const {
    return dangerTemp;
}

void Vehicle::updatePhysics() {
    if (isOn) {
        if (engineTemp <= warmedUpEngineTemp) {
            warmingUpTheEngine();
        } else if (engineTemp >= dangerTemp) {
            collingCriticEngineTemp();
        } else if (engineTemp >= warmedUpEngineTemp) {
            engineTemperatureMaintenance();
        }
    } else if (!isOn && engineTemp >= cooledEngineTemperature) {
        restingDownTheEngine();
    }


    if (fuel > outOfFuel) {
        updateFuel();
    }
}

void Vehicle::isOKToStartVehicle() {
    if (!isOn && engineTemp < dangerTemp && fuel > outOfFuel) {
        isOn = true;
    }
}

double Vehicle::getRandomTemperature() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist1(3, 18);
    std::uniform_real_distribution<> dist2(2, 13);
    if (type == Type::ElectricVehicle) {
        return dist1(gen);
    }
    return (dist1(gen) + dist2(gen)) / 2;
}

void Vehicle::warmingUpTheEngine() {
    engineTemp += getRandomTemperature();
}

void Vehicle::restingDownTheEngine() {
    engineTemp -= getRandomTemperature();

    if (engineTemp <= cooledEngineTemperature) {
        engineTemp = cooledEngineTemperature;
    }
}

void Vehicle::engineTemperatureMaintenance() {
    static std::uint8_t plusMinus{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> newTemp(1, 7);

    const double chanceOfCriticalTemperature{newTemp(gen)};

    if (engineTemp >= warningTemp) {
        plusMinus = 1;
    }

    if (!plusMinus) {
        if (chanceOfCriticalTemperature <= 2) {
            engineTemp += newTemp(gen) + 30;
        } else {
            engineTemp += newTemp(gen);
        }
        plusMinus = 1;
    } else {
        engineTemp -= newTemp(gen);
        plusMinus = 0;
    }
}

void Vehicle::collingCriticEngineTemp() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(5, 15);

    engineTemp -= dist(gen);
}

void Vehicle::updateFuel() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 2);
    fuel -= dist(gen);

    if (fuel <= outOfFuel) {
        fuel = outOfFuel;
        isOn = false;
    }
}
