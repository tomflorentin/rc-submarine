//
// Created by tomfl on 3/19/2023.
//

#include "LedController.hpp"


void LedController::setBrightness(uint8_t value) {
    uint8_t powerDraw = 0;
    if (this->leftOn) {
        powerDraw += value / 2;
        this->ledLeft.write(value);
    }
    if (this->rightOn) {
        powerDraw += value / 2;
        this->ledRight.write(value);
    }
    this->currentBrightness = value;
    this->drawPower(powerDraw);
}

void LedController::setup() {
    this->ledRight.setup();
    this->ledLeft.setup();
}

void LedController::right(bool state) {
    this->rightOn = state;
    this->setBrightness(this->currentBrightness);
}

void LedController::left(bool state) {
    this->leftOn = state;
    this->setBrightness(this->currentBrightness);
}

LedController::LedController(uint8_t _pinRight, uint8_t _pinLeft) : IPowerMonitorable(20), ledRight(_pinRight), ledLeft(_pinLeft) {
}
