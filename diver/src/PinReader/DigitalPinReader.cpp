//
// Created by tomfl on 3/18/2023.
//

#include <Arduino.h>
#include "DigitalPinReader.hpp"

bool DigitalPinReader::read() const {
    return digitalRead(this->pin);
}

void DigitalPinReader::setup() {
    pinMode(this->pin, this->readMode);
}

DigitalPinReader::DigitalPinReader(uint8_t pin, bool pullup) : PinManager(pin) {
    this->pin = pin;
    this->readMode = pullup ? INPUT_PULLUP : INPUT;
}
