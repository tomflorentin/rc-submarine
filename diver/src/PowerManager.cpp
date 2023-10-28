//
// Created by tomfl on 5/16/2023.
//

#include <Arduino.h>
#include "PowerManager.hpp"
#include "func.hpp"

PowerManager *PowerManager::instance = nullptr;

PowerManager::PowerManager() {
    PowerManager::instance = this;
}

void PowerManager::drawPower(int id, float watts) {
    unsigned long now = millis();
    int foundIndex = this->findDevice(id);

    if (foundIndex == -1) {
        if (this->currentIndex >= MAX_DEVICES)
            return;
        this->registerDevice(id, this->currentIndex++, watts, now);
    } else {
        this->calcPower(foundIndex, now);
        this->registerDevice(id, foundIndex, watts, now);
    }
}


int PowerManager::findDevice(int id) {
    int foundId = -1;
    for (unsigned short i = 0; i < this->currentIndex; i++) {
        if (this->devicesIds[i] == id) {
            foundId = i;
            break;
        }
    }
    return foundId;
}

void PowerManager::registerDevice(int id, unsigned short index, float watts, unsigned long now) {
    this->devicesIds[index] = id;
    this->devicesCurrentDraw[index] = watts;
    this->devicesLastCalc[index] = now;
}

void PowerManager::calcPower(unsigned short index, unsigned long now) {
    unsigned long timeDiff = now - this->devicesLastCalc[index];
    this->totalPowerDrawn += (float)this->devicesCurrentDraw[index] * ((float)timeDiff / 1000.f);
    this->devicesLastCalc[index] = now;
}

void PowerManager::work() {
    for (unsigned short i = 0; i < this->currentIndex; i++) {
        this->calcPower(i, millis());
    }
}

unsigned short PowerManager::getTotalPowerDrawn() const {
    return (unsigned short)this->totalPowerDrawn;
}

unsigned short PowerManager::getInstantPower() const {
    float totalPower = 0;
    for (unsigned short i = 0; i < this->currentIndex; i++) {
        totalPower += this->devicesCurrentDraw[i];
    }
    return (unsigned short)totalPower;
}
