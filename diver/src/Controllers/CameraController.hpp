//
// Created by tomfl on 3/29/2023.
//

#ifndef EMBARQUE_CAMERACONTROLLER_HPP
#define EMBARQUE_CAMERACONTROLLER_HPP

#include "../lib/Servo.hpp"
#include <stdint.h>
#include "Interfaces/ISetupable.hpp"
#include "PinReader/DigitalPinWriter.hpp"

class CameraController : public ISetupable {
public:
    CameraController(uint8_t servoPin);

    void setup() override;
    void setAngle(uint8_t angle);
private:
    Servo servo;
    uint8_t servoPin;
};


#endif //EMBARQUE_CAMERACONTROLLER_HPP
