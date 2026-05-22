cmake_minimum_required(VERSION 4.2)
project(telemetryAndVehicleFleetSystem)

set(CMAKE_CXX_STANDARD 23)

add_executable(telemetryAndVehicleFleetSystem main.cpp
        src/Vehicle.cpp
        include/Vehicle.h
        include/Car.h
        src/Car.cpp)
