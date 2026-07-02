#pragma once
#include "SystemUI.h"
#include "Vehicle.h"
#include <memory>
#include <vector>
#include <filesystem>

class System {
public:
    System(const System &) = delete;

    System &operator=(const System &) = delete;

    static System &getInstace() {
        static System sys;
        return sys;
    }

    void run();

private:
    System();

    std::unique_ptr<SystemUI> sysUI;
    std::vector<std::unique_ptr<Vehicle> > vehicles;

    inline static const std::filesystem::path vehiclesPath{DATA_DIR "vehicles.csv"};

    [[nodiscard]] static bool isVehiclesFileExists();

    static void createVehiclesFile();

    void loadVehiclesFromFile();

    void readFileLine(const std::string &line);

    void addVehicleToVar(std::unique_ptr<Vehicle> vehicle);

    void startSimulation() const;

    static void handleExit(int signum);

    static void cursorBackAndCleaningBottom();

    static void hideCursorPosition();

    static void saveCursorPosition();
};
