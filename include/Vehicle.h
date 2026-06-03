#pragma once
#include <string>

class Vehicle {
public:
  std::string name;
  double fuel{};
  double enginePower;
  bool isON{};
  std::string type;

  Vehicle(const std::string &name, double fuel, double enginePower, const std::string &type)
      : name(std::move(name)), fuel(fuel), enginePower(enginePower), type(std::move(type)) {}
  virtual ~Vehicle() = default;
};