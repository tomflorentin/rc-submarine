////
//// Created by tomfl on 4/25/2023.
////
//
//#ifndef EMBARQUE_TEMPERATURESENSOR_HPP
//#define EMBARQUE_TEMPERATURESENSOR_HPP
//
//
//#include "lib/OneWire.hpp"
//#include "lib/DallasTemperature.hpp"
//#include "Interfaces/ISetupable.hpp"
//#include <stdint.h>
//
//class TemperatureSensor : public ISetupable {
//public:
//    explicit TemperatureSensor(uint8_t _pin);
//    float getTemperature();
//
//    void setup() override;
//
//    private:
//    uint8_t pin;
//    OneWire oneWire;
//
//// Pass our oneWire reference to Dallas Temperature sensor
//    DallasTemperature sensors;
//};
//
//
//#endif //EMBARQUE_TEMPERATURESENSOR_HPP
