//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_L298CONTROLLER_HPP
#define EMBARQUE_L298CONTROLLER_HPP


#include <stdint.h>
#include "PinReader/AnalogPinWriter.hpp"
#include "Interfaces/ISetupable.hpp"
#include "Interfaces/IBridgeController.hpp"

class L298Controller : public IBridgeController {
public:
    L298Controller(uint8_t in1, uint8_t in2, unsigned short maxWatts);
    void forward(uint8_t speed) override;
    void backward(uint8_t speed) override;
    void brake() override;
    void standby() override;
    void setup() override;

private:
    AnalogPinWriter pin1;
    AnalogPinWriter pin2;
};


#endif //EMBARQUE_L298CONTROLLER_HPP
