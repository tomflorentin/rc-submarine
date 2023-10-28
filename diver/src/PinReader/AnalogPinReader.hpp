//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_ANALOGPINREADER_HPP
#define EMBARQUE_ANALOGPINREADER_HPP


#include "PinManager.hpp"

#define MAX_VOLTS_READ 1023.f
#define MAX_VOLTS_ELECTRIC 5.f

class AnalogPinReader : public PinManager {
public:
    AnalogPinReader(uint8_t pin);
    AnalogPinReader(uint8_t pin, float _minVolts, float _maxVolts, float _minValue, float _maxValue);
    void configureMap(float _minVolts, float _maxVolts, float _minValue, float _maxValue);

    float readMap() const;
    int readRaw() const;

    void setup() override;

protected:
    float in_min;
    float in_max;
    float out_min;
    float out_max;
    bool mapConfigured = false;

};


#endif //EMBARQUE_ANALOGPINREADER_HPP
