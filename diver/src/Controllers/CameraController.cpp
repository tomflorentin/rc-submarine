//
// Created by tomfl on 3/29/2023.
//

#include <Arduino.h>
#include "CameraController.hpp"
#include "func.hpp"

CameraController::CameraController(uint8_t servoPin) : servoPin(servoPin) {

}

void CameraController::setup() {
    pinMode(servoPin, OUTPUT);
    servo.attach(servoPin);
    servo.write(90);
}

void CameraController::setAngle(uint8_t angle) {
    if (angle < 20 || angle > 150) {
        // Log("Angle must be between 20 and 150");
        return;
    }
    // Log("Setting camera angle to " + String(angle));
    this->servo.write(angle);
}
