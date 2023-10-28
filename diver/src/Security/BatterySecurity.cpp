//
// Created by tomfl on 3/24/2023.
//

#include "BatterySecurity.hpp"

BatterySecurity::BatterySecurity(BatteryLevelSensor *_batterySensor) : sensor(_batterySensor) {
}

Alert BatterySecurity::checkSecurity() {
    uint8_t level = sensor->getLevel();
    if (level <= 20)
        return Alert::LowBattery;
    return Alert::None;
}
