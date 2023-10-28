//
// Created by tomfl on 3/19/2023.
//

#include "DepthSensor.hpp"

DepthSensor::DepthSensor(uint8_t pin) : pressureSensor(pin){
    this->pressureSensor.configureMap(0.5, 4.5, 0, 6.89476);
}

void DepthSensor::setup() {
    pressureSensor.setup();
}

float DepthSensor::getDepth() {
    float pressure = pressureSensor.readMap();
    return (pressure - 1) * 10;
}

float DepthSensor::getPressure() {
    return pressureSensor.readMap();
}


