//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_BTS7960CONTROLLER_HPP
#define EMBARQUE_BTS7960CONTROLLER_HPP


#include <stdint.h>
#include "PinReader/AnalogPinWriter.hpp"
#include "Interfaces/ISetupable.hpp"
#include "Interfaces/IBridgeController.hpp"
#include "PinReader/DigitalPinWriter.hpp"

class BTS7960Controller : public IBridgeController {
public:
    BTS7960Controller(uint8_t lpwmPin, uint8_t rpwmPin, uint8_t lenPin, uint8_t renPin, unsigned short maxWatts);
    void forward(uint8_t speed) override;
    void backward(uint8_t speed) override;
    void brake() override;
    void standby() override;
    void setup() override;

private:
    AnalogPinWriter lpwm;
    AnalogPinWriter rpwm;
    DigitalPinWriter len;
    DigitalPinWriter ren;
};


#endif //EMBARQUE_BTS7960CONTROLLER_HPP
