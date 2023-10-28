//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_ULTRASONICSENSOR_HPP
#define EMBARQUE_ULTRASONICSENSOR_HPP


#include <stdint.h>
#include "PinReader/DigitalPinWriter.hpp"
#include "PinReader/DigitalPinReader.hpp"

class UltrasonicSensor : public ISetupable {
public:
    explicit UltrasonicSensor(uint8_t _triggerPin, uint8_t _echoPin);

    float getDistance(int cacheMilleseconds = 100);
    void setup() override;

private:
    float readDistance(signed char numberOfCalc = 3);
    float readRawDistance();

    DigitalPinWriter triggerPin;
    DigitalPinReader echoPin;

    float lastDistance = 0;
    unsigned long lastDistanceTime = 0;
};


#endif //EMBARQUE_ULTRASONICSENSOR_HPP
