//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_LEDCONTROLLER_HPP
#define EMBARQUE_LEDCONTROLLER_HPP


#include <stdint.h>
#include "L298Controller.hpp"

class LedController : public ISetupable, public IPowerMonitorable {
public:
    explicit LedController(uint8_t _pinRight, uint8_t _pinLeft);

    void right(bool state);
    void left(bool state);
    void setBrightness(uint8_t value);
    void setup() override;
private:
    uint8_t currentBrightness = 0;
    bool rightOn = false;
    bool leftOn = false;

    AnalogPinWriter ledRight;
    AnalogPinWriter ledLeft;
};


#endif //EMBARQUE_LEDCONTROLLER_HPP
