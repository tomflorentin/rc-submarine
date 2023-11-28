//
// Created by tomfl on 3/19/2023.
//

#include <Arduino.h>
#include "EngineController.hpp"
#include "func.hpp"

const short TIME_TO_ACCELERATE = 10000;
const float ACCELERATION_COEFF = 255.f / TIME_TO_ACCELERATE;

EngineController::EngineController(uint8_t right_rpwm, uint8_t right_lpwm,
                                   uint8_t left_rpwm, uint8_t left_lpwm) :
        rightMotor(right_lpwm, right_rpwm, 100),
        leftMotor(left_lpwm, left_rpwm, 100) {}


void EngineController::setup() {
    this->rightMotor.setup();
    this->leftMotor.setup();
}

void EngineController::move(uint8_t forward, uint8_t turn, uint8_t speedCoeff, uint8_t turnCoeff) {
    this->lastOrderTime = millis();

    if (isLocked) {
        return;
    }
    if (forward > 150) {
        this->targetRightSpeed = map(forward, 127, 255, 0, speedCoeff);
        this->targetLeftSpeed = map(forward, 127, 255, 0, speedCoeff);
    } else if (forward < 100) {
        this->targetRightSpeed = -map(forward, 0, 127, 0, speedCoeff);
        this->targetLeftSpeed = -map(forward, 0, 127, 0, speedCoeff);
    } else {
        if (turn > 150) {
            this->targetRightSpeed = -turnCoeff;
            this->targetLeftSpeed = turnCoeff;
        } else if (turn < 100) {
            this->targetRightSpeed = turnCoeff;
            this->targetLeftSpeed = -turnCoeff;
        }
    }
}


void EngineController::lock() {
    this->isLocked = true;
    this->rightMotor.standby();
    this->leftMotor.standby();
}

void EngineController::unlock() {
    this->isLocked = false;
}

void EngineController::work() {
    unsigned long now = millis();
    if (now - this->lastOrderTime > 500) {
        if (this->targetRightSpeed) {
            // Log("Stopped because no order for too long");
        }
        this->targetRightSpeed = 0;
        this->targetLeftSpeed = 0;
        this->rightMotor.standby();
        this->leftMotor.standby();
    }

    if (now - this->lastSpeedChange > 100) {
        this->currentRightSpeed = this->calcNewSpeed(this->targetRightSpeed,
                                                     this->currentRightSpeed,
                                                     now - this->lastSpeedChange);
        this->currentLeftSpeed = this->calcNewSpeed(this->targetLeftSpeed,
                                                    this->currentLeftSpeed,
                                                    now - this->lastSpeedChange);

        if (this->currentRightSpeed > 0) {
            this->rightMotor.forward(this->currentRightSpeed);
        } else if (this->currentRightSpeed < 0) {
            this->rightMotor.backward(-this->currentRightSpeed);
        } else {
            this->rightMotor.standby();
        }
        if (this->currentLeftSpeed > 0) {
            this->leftMotor.forward(this->currentLeftSpeed);
        } else if (this->currentLeftSpeed < 0) {
            this->leftMotor.backward(-this->currentLeftSpeed);
        } else {
            this->leftMotor.standby();
        }
        this->lastSpeedChange = millis();
    }

}

short EngineController::calcNewSpeed(short targetSpeed, short currentSpeed, unsigned long timeDiff) {
    if (targetSpeed == currentSpeed) {
        return currentSpeed;
    }
    auto absTargetSpeed = abs(targetSpeed);
    auto absCurrentSpeed = abs(currentSpeed);
    auto multiplicator = targetSpeed >= 0 ? 1 : -1;

    if (targetSpeed == 0)
        return 0;
    if (absCurrentSpeed < absTargetSpeed) {
        short newSpeed = min(absTargetSpeed, absCurrentSpeed + timeDiff * ACCELERATION_COEFF);
        if (newSpeed < 10)
            newSpeed *= 2;
        newSpeed *= multiplicator;
        return newSpeed;
    } else {
        return 0;
    }
}
