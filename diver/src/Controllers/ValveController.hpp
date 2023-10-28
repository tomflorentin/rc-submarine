//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_VALVECONTROLLER_HPP
#define EMBARQUE_VALVECONTROLLER_HPP


#include "PinReader/DigitalPinWriter.hpp"
#include "Interfaces/ISetupable.hpp"
#include "Interfaces/IPowerMonitorable.hpp"

class ValveController : public ISetupable, public IPowerMonitorable {
public:
    explicit ValveController(uint8_t _pin);

    void open();
    void close();

    void setup() override;

private:
    DigitalPinWriter pin;
};


#endif //EMBARQUE_VALVECONTROLLER_HPP
