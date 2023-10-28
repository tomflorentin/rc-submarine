//
// Created by tomfl on 5/15/2023.
//

#ifndef EMBARQUE_IBRIDGECONTROLLER_HPP
#define EMBARQUE_IBRIDGECONTROLLER_HPP


#include <stdint.h>
#include <new>
#include "PinReader/AnalogPinWriter.hpp"
#include "Interfaces/ISetupable.hpp"
#include "IPowerMonitorable.hpp"

class IBridgeController : public ISetupable, public IPowerMonitorable {
public:
    virtual void setSpeed(signed char speed);
    virtual void forward(uint8_t speed) = 0;
    virtual void backward(uint8_t speed) = 0;
    virtual void brake() = 0;
    virtual void standby() = 0;
    void setup() override = 0;

protected:
    explicit IBridgeController(unsigned short maxWatts);
};

#endif //EMBARQUE_IBRIDGECONTROLLER_HPP
