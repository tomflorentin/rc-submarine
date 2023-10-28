//
// Created by tomfl on 3/18/2023.
//

#include <Arduino.h>
#include "DigitalPinWriter.hpp"

DigitalPinWriter::DigitalPinWriter(uint8_t pin) : PinManager(pin) {
}

void DigitalPinWriter::write(bool value) const {
    digitalWrite(this->pin, value);
}

void DigitalPinWriter::setup() {
    pinMode(this->pin, OUTPUT);
    digitalWrite(this->pin, false);
}
