//
// Created by tomfl on 3/24/2023.
//

#include "BatteryLevelSensor.hpp"

BatteryLevelSensor::BatteryLevelSensor(uint8_t pin) : voltMetter(pin) {

}

void BatteryLevelSensor::setup() {
    this->voltMetter.setup();
}

uint8_t BatteryLevelSensor::getLevel() {
    return 60;
}
