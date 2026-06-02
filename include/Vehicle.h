#pragma once
#include <string>

class Vehicle {
public:
  std::string name;
  double fuel{};
  double enginePower;
  bool isON{};
  std::string type;

  Vehicle(const std::string &n, double eP, double f, const std::string &type)
      : name(std::move(n)), fuel(f), enginePower(eP), type(std::move(type)) {}
  virtual ~Vehicle() = default;
};