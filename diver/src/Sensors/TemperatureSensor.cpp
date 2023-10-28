//
// Created by tomfl on 4/25/2023.
//

#include "TemperatureSensor.hpp"
#include "func.hpp"

TemperatureSensor::TemperatureSensor(uint8_t _pin) : pin(_pin), oneWire(_pin), sensors(&oneWire) {
}

void TemperatureSensor::setup() {
    oneWire.begin(this->pin);
    sensors.begin();
    pinMode(this->pin, INPUT);
}

float TemperatureSensor::getTemperature() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}


