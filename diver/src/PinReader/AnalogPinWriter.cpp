//
// Created by tomfl on 3/19/2023.
//

#include <Arduino.h>
#include "AnalogPinWriter.hpp"

AnalogPinWriter::AnalogPinWriter(uint8_t pin) : PinManager(pin) {
}

void AnalogPinWriter::write(uint8_t value) const {
    analogWrite(this->pin, value);
}

void AnalogPinWriter::setup() {
    pinMode(this->pin, OUTPUT);
}
