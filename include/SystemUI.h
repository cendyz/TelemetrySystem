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

    static constexpr std::string_view electricCarType{"electric"};

    void printInitializationMessages() const;

    void printVehiclesFileIsEmpty() const;

    void printAddedVehicle(const std::vector<std::unique_ptr<Vehicle> > &vehicles,
                           std::string_view electricCar) const;

    void printTelemetricSimulation(const std::unique_ptr<Vehicle> &obj) const;

    void printSimulationStartHeader();

    static constexpr std::uint8_t normalEngTemp{105};
    static constexpr std::uint8_t dangerEngTemp{115};

    void printEngineWarning() const;

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

    void printCarNameInfo(const std::string &name, std::string_view color) const;

    void printIsRunning(bool isOn) const;

    void printEngineTemp(double temp) const;

    void printFuel(double fuel) const;


};
