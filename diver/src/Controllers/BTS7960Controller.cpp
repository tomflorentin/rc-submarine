//
// Created by tomfl on 5/15/2023.
//
#include "BTS7960Controller.hpp"
#include "func.hpp"

BTS7960Controller::BTS7960Controller(uint8_t lpwmPin, uint8_t rpwmPin, uint8_t lenPin, uint8_t renPin,
                                     unsigned short maxWatts) : IBridgeController(maxWatts),
                                                                lpwm(lpwmPin), rpwm(rpwmPin), len(lenPin),
                                                                ren(renPin) {}

void BTS7960Controller::setup() {
    lpwm.setup();
    rpwm.setup();
    len.setup();
    ren.setup();
}

void BTS7960Controller::forward(uint8_t speed) {
//    Log("Forward " + String(speed));
    len.write(true);
    ren.write(false);
    lpwm.write(speed);
    rpwm.write(0);
    this->drawPower(speed);
}

void BTS7960Controller::backward(uint8_t speed) {
//    Log("Backward " + String(speed));
    len.write(false);
    ren.write(true);
    lpwm.write(0);
    rpwm.write(speed);
    this->drawPower(speed);
}

void BTS7960Controller::brake() {
    len.write(true);
    ren.write(true);
    lpwm.write(255);
    rpwm.write(255);
    this->drawPower(255);
}

void BTS7960Controller::standby() {
    len.write(false);
    ren.write(false);
    lpwm.write(0);
    rpwm.write(0);
    this->drawPower(0);
}

