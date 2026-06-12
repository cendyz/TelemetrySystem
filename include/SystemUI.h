#pragma once
#include "LanguageManager.h"
#include "Vehicle.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

class SystemUI {
public:
    SystemUI();

    ~SystemUI() = default;

    void printInitializationMessages() const;

    void printVehiclesFileIsEmpty() const;
    void printAddedVehicle(const std::vector<std::unique_ptr<Vehicle> > &vehicles) const;

    void printTelemetricSimulation(const std::unique_ptr<Vehicle> &obj) const;

    void printSimulationStartHeader();

    [[nodiscard]] std::string getArrowMsg(const std::string & msg) const;

    void printEngineWarning() const;
    void printEngineDanger() const;

    void printMediumFuelLevel() const;
    void printLowFuelLevel() const;
    void printNoFuel() const;

    void pritnAllOkInfo() const;

private:
    std::unique_ptr<LanguageManager> langManager;

    [[nodiscard]] static std::string getSystemLang();

    static constexpr std::string_view choseLangInputMsg{
        "Select the log display language (JP/EN): "
    };
    static constexpr std::string_view jpLen{"jp"};
    static constexpr std::string_view enLen{"en"};

    static constexpr std::string_view wrongLangInputMsg{"Invalid command."};

    [[nodiscard]] static bool itIsJapaneseLanguage();

    void setLanguage();

    inline static const std::array<std::string, 2> systems_k{
        "S_BOOT",
        "S_INFO"
    };
    inline static const std::array<std::string, 2> inits_k{"INIT", "LANG_L"};

    int tickNum{1};

    void printCarNameInfo(std::string_view name, std::string_view color, const bool &isOn, double fuel) const;

    void printIsRunning(bool isOn) const;

    void printEngineTemp(double temp, double warningTemp, double dangerTemp) const;

    void printFuel(const std::unique_ptr<Vehicle> &obj) const;

};
