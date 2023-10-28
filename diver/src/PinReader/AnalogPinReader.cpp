//
// Created by tomfl on 3/19/2023.
//

#include <Arduino.h>
#include "AnalogPinReader.hpp"

AnalogPinReader::AnalogPinReader(uint8_t pin) : PinManager(pin) {
}

void AnalogPinReader::configureMap(float _minVolts, float _maxVolts, float _minValue, float _maxValue) {
    this->in_min = (_minVolts * MAX_VOLTS_READ) / MAX_VOLTS_ELECTRIC;
    this->in_max = (_maxVolts * MAX_VOLTS_READ) / MAX_VOLTS_ELECTRIC;
    this->out_min = _minValue;
    this->out_max = _maxValue;
    this->mapConfigured = true;
}

float AnalogPinReader::readMap() const {
    int value = analogRead(this->pin);
    return ((float)value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int AnalogPinReader::readRaw() const {
    return analogRead(this->pin);
}

AnalogPinReader::AnalogPinReader(uint8_t pin, float _minVolts, float _maxVolts, float _minValue, float _maxValue) : PinManager(pin) {
    this->configureMap(_minVolts, _maxVolts, _minValue, _maxValue);
}

void AnalogPinReader::setup() {
    pinMode(this->pin, INPUT);
}
