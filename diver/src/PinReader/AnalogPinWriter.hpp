//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_ANALOGPINWRITER_HPP
#define EMBARQUE_ANALOGPINWRITER_HPP


#include <stdint.h>
#include "PinManager.hpp"

class AnalogPinWriter : public PinManager {
public:
    explicit AnalogPinWriter(uint8_t pin);

    void write(uint8_t value) const;
    void setup() override;
};


#endif //EMBARQUE_ANALOGPINWRITER_HPP
