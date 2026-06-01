#pragma once
#include <string>

class Vehicle {
public:
  std::string name;
  double fuel{};
  double enginePower;
  bool isON{};
  
  Vehicle(const std::string &n, double eP, double f) : name(std::move(n)), fuel(f), enginePower(eP) {}
  virtual ~Vehicle() = default;

  // virtual void start() = 0;
  // virtual void turnOff() = 0;
  // virtual void turnRightLeft() = 0;
};
