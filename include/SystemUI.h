#pragma once
#include "LanguageManager.h"
#include <array>
#include <memory>
#include <string>
#include <vector>
#include "Vehicle.h"

class SystemUI {
public:
  SystemUI();

  ~SystemUI() = default;

  void printInitializationMessages() const;
  void printVehiclesFileIsEmpty() const;
  void printAddedVehicle(const std::vector<std::unique_ptr<Vehicle>> &vehicles, std::string_view electricCar) const;
private:
  std::unique_ptr<LanguageManager> langManager;

  [[nodiscard]] static std::string getSystemLang();
  static constexpr std::string_view choseLangInputMsg{
      "Select the log display language (JP/EN): "};
  static constexpr std::string_view jpLen{"jp"};
  static constexpr std::string_view enLen{"en"};

  static constexpr std::string_view wrongLangInputMsg{"Invalid command."};
  [[nodiscard]] static bool itIsJapaneseLanguage();

  void setLanguage();

  inline static constexpr std::array<std::string, 2> systems_k{"S_BOOT", "S_INFO"};
  inline static constexpr std::array<std::string, 2> inits_k{"INIT", "LANG_L"};
};
