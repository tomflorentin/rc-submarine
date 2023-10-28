//
// Created by tomfl on 3/24/2023.
//

#ifndef EMBARQUE_WATERSECURITY_HPP
#define EMBARQUE_WATERSECURITY_HPP


#include <stdint.h>
#include "PinReader/DigitalPinReader.hpp"
#include "Security.hpp"
#include "PinReader/AnalogPinReader.hpp"

class WaterSecurity : public ISetupable, public Security {
public:
    WaterSecurity(uint8_t pinFront, uint8_t pinBack, uint8_t pinSeringueGasket, uint8_t pinSeringueOut);

    Alert checkSecurity() override;
    void setup() override;
private:
    AnalogPinReader front;
    AnalogPinReader back;
    AnalogPinReader seringueGasket;
    AnalogPinReader seringueOut;
};


#endif //EMBARQUE_WATERSECURITY_HPP
