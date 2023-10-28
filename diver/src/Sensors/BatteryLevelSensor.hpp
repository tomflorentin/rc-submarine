//
// Created by tomfl on 3/24/2023.
//

#ifndef EMBARQUE_BATTERYLEVELSENSOR_HPP
#define EMBARQUE_BATTERYLEVELSENSOR_HPP


#include <stdint.h>
#include "PinReader/AnalogPinReader.hpp"

class BatteryLevelSensor : ISetupable {
public:
    explicit BatteryLevelSensor(uint8_t pin);
    void setup() override;

    uint8_t getLevel();

private:
    AnalogPinReader voltMetter;

};


#endif //EMBARQUE_BATTERYLEVELSENSOR_HPP
