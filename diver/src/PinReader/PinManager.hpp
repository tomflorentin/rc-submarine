//
// Created by tomfl on 3/18/2023.
//

#ifndef EMBARQUE_PINMANAGER_HPP
#define EMBARQUE_PINMANAGER_HPP


#include <stdint.h>
#include "Interfaces/ISetupable.hpp"

class PinManager : public ISetupable {
public:
    uint8_t getPin() const;

protected:
    PinManager(uint8_t pin);

    int pin;
};


#endif //EMBARQUE_PINMANAGER_HPP
