//
// Created by tomfl on 3/18/2023.
//

#include "PinManager.hpp"

#ifndef EMBARQUE_DIGITALPINWRITER_HPP
#define EMBARQUE_DIGITALPINWRITER_HPP


class DigitalPinWriter : public PinManager {
public:
    DigitalPinWriter(uint8_t pin);

    void write(bool value) const;
    void setup() override;
};


#endif //EMBARQUE_DIGITALPINWRITER_HPP
