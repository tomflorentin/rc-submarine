//
// Created by tomfl on 3/27/2023.
//

#ifndef EMBARQUE_SENSORMONITOR_HPP
#define EMBARQUE_SENSORMONITOR_HPP


#include "DHT.hpp"
#include "DepthSensor.hpp"
#include "RemoteControl/RemoteControl.hpp"
#include "BatteryLevelSensor.hpp"
#include "TemperatureSensor.hpp"

class SensorMonitor {
public:
    SensorMonitor(RemoteControl *_control, TemperatureSensor *_temperature, DepthSensor *_insidePressure, BatteryLevelSensor *_batteryLevelSensor);
    void work();

private:
    unsigned long lastRead = 0;

    RemoteControl *control;
    TemperatureSensor *temperatureSensor;
    DepthSensor *insidePressure;
    BatteryLevelSensor *batteryLevelSensor;
};


#endif //EMBARQUE_SENSORMONITOR_HPP
