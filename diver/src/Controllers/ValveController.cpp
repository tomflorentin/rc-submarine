//
// Created by tomfl on 3/19/2023.
//

#include "ValveController.hpp"

ValveController::ValveController(uint8_t _pin) : IPowerMonitorable(4), pin(_pin) {

}

void ValveController::open() {
    this->drawPower(255);
    this->pin.write(true);
}

void ValveController::close() {
    this->drawPower(0);
    this->pin.write(false);
}

void ValveController::setup() {
    this->pin.setup();
}

