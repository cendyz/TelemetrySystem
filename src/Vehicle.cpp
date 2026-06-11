#include <Vehicle.h>

void Vehicle::updatePhysics() {
    if (isON) {
        if (engineTemp <= warmedUpEngineTemp) {
            warmingUpTheEngine();
        } else if (engineTemp >= dangerTemp) {
            collingCriticEngineTemp();
        } else if (engineTemp >= warmedUpEngineTemp) {
            engineTemperatureMaintenance();
        }
    } else if (isON && engineTemp >= cooledEngineTemperature) {
        restingDownTheEngine();
    }


    if (fuel > outOfFuel) {
        updateFuel(fuel, isON);
    }
}
