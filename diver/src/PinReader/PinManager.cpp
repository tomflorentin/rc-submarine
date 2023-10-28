//
// Created by tomfl on 3/18/2023.
//

#include "PinManager.hpp"

PinManager::PinManager(uint8_t _pin) : pin(_pin){
}

uint8_t PinManager::getPin() const {
    return this->pin;
}
