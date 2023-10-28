//
// Created by tomfl on 3/19/2023.
//

#include <WString.h>
#include "L298Controller.hpp"
#include "func.hpp"

L298Controller::L298Controller(uint8_t in1, uint8_t in2, unsigned short maxWatts)
        : IBridgeController(maxWatts),
          pin1(in1),
          pin2(in2) {}

void L298Controller::forward(uint8_t speed) {
    this->pin2.write(0);
    this->pin1.write(speed);
}

void L298Controller::backward(uint8_t speed) {
    this->pin1.write(0);
    this->pin2.write(speed);
}

void L298Controller::brake() {
    this->pin1.write(255);
    this->pin2.write(255);
}

void L298Controller::standby() {
    this->pin1.write(0);
    this->pin2.write(0);
}

void L298Controller::setup() {
    this->pin1.setup();
    this->pin2.setup();
}
