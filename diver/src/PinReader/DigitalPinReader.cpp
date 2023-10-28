//
// Created by tomfl on 3/18/2023.
//

#include <Arduino.h>
#include "DigitalPinReader.hpp"

DigitalPinReader::DigitalPinReader(uint8_t pin) : PinManager(pin) {
}

bool DigitalPinReader::read() const {
    return digitalRead(this->pin);
}

void DigitalPinReader::setup() {
    pinMode(this->pin, INPUT);
}
