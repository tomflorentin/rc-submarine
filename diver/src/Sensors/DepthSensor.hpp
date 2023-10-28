//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_DEPTHSENSOR_HPP
#define EMBARQUE_DEPTHSENSOR_HPP


#include <stdint.h>
#include "Interfaces/ISetupable.hpp"
#include "PinReader/AnalogPinReader.hpp"

class DepthSensor : public ISetupable {
public:
    explicit DepthSensor(uint8_t pin);
    void setup() override;

    float getDepth();
    float getPressure();

private:
    AnalogPinReader pressureSensor;
};


#endif //EMBARQUE_DEPTHSENSOR_HPP
