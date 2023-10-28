//
// Created by tomfl on 3/19/2023.
//

#include <Arduino.h>
#include "DepthController.hpp"

// Constante de correction proportionnelle
const float Kp = 0.1;



DepthController::DepthController(BallastController *_ballast, DepthSensor *_depthSensor) : ballast(_ballast),
                                                                                           depthSensor(_depthSensor) {

}

void DepthController::work() {
    if (!depthSensor)
        return;

    unsigned long now = millis();
    if (now - lastDepthsTime[lastDepthsIndex] > 100) {
        this->storeDepth();
    }
    float lastDepth = lastDepths[lastDepthsIndex];

    if (!ballast)
        return;

    if (this->emergencyMode == EmergencyMode::FLOAT) {
        this->ballast->empty();
        return;
    }
    if (this->emergencyMode == EmergencyMode::SEAL) {
        this->ballast->standby();
        return;
    }

    if (!this->isTargetingDepth && this->isTargetingSpeed && this->lastManualDiveOrderTime - now > 500) {
        this->stabilize();
    }

    if (this->isTargetingDepth) {
        float delta = this->targetDepth - lastDepth;
        float speed = this->getDesiredSpeedForDelta(delta);
        this->isTargetingSpeed = true;
        this->verticalSpeed = speed;
    }

    if (this->isTargetingSpeed) {
        VerticalSpeedCorrection correction = NO_CORRECTION;

        if (abs(abs(this->targetSpeed) - abs(this->verticalSpeed)) < this->targetSpeed * 0.2) {
            correction = NO_CORRECTION;
        } else if (this->targetSpeed > this->verticalSpeed) {
            correction = INCREASE;
        } else if (this->targetSpeed < this->verticalSpeed) {
            correction = DECREASE;
        }

        if (correction == INCREASE) {
            if (this->verticalSpeed > 0) {
                this->ballast->empty();
            } else {
                this->ballast->fill();
            }
        } else if (correction == DECREASE) {
            if (this->verticalSpeed > 0) {
                this->ballast->fill();
            } else {
                this->ballast->empty();
            }
        } else {
            this->ballast->standby();
        }
    }

}

void DepthController::setTargetDepth(float _depth) {
    this->targetDepth = _depth;
    this->isTargetingDepth = true;
    this->targetSpeed = 0;
    this->isTargetingSpeed = false;
}

void DepthController::setVerticalSpeed(float _speed) {
    this->lastManualDiveOrderTime = millis();
    this->targetDepth = -1;
    this->isTargetingDepth = false;
    this->isTargetingSpeed = true;
    this->targetSpeed = _speed;
}

void DepthController::stabilize() {
    float depth = this->depthSensor->getDepth();
    this->isTargetingDepth = true;
    this->setTargetDepth(depth);
}

float DepthController::getVerticalSpeed() {
    return this->verticalSpeed;
}

void DepthController::storeDepth() {
    lastDepths[lastDepthsIndex] = this->depthSensor->getDepth();
    lastDepthsTime[lastDepthsIndex] = millis();
    lastDepthsIndex = (lastDepthsIndex + 1) % NUMBER_OF_LAST_DEPTHS;
    this->lastDepthsIndex += 1;

    double totalVerticalVelocity = 0.0;
    int numPairs = 0;

    for (int i = 0; i < NUMBER_OF_LAST_DEPTHS - 1; i++) {
        int j = (lastDepthsIndex - 1 - i + NUMBER_OF_LAST_DEPTHS) % NUMBER_OF_LAST_DEPTHS;
        int k = (lastDepthsIndex - 2 - i + NUMBER_OF_LAST_DEPTHS) % NUMBER_OF_LAST_DEPTHS;
        double depthDiff = (lastDepths[j] - lastDepths[k]) * 100; // cm
        double timeDiff = (lastDepthsTime[j] - lastDepthsTime[k]) * 0.001; // seconds
        if (timeDiff > 0) {
            double verticalVelocity = depthDiff / timeDiff;
            totalVerticalVelocity += verticalVelocity;
            numPairs++;
        }
    }

    if (numPairs > 0) {
        double avgVerticalVelocity = totalVerticalVelocity / numPairs;
        this->verticalSpeed = avgVerticalVelocity;
    }
}

void DepthController::stopAll() {
    this->targetDepth = -1;
    this->isTargetingDepth = false;
    this->isTargetingSpeed = false;
    this->targetSpeed = 0;
}

float DepthController::getDesiredSpeedForDelta(float _delta) {
    float absDelta = abs(_delta);
    float speed = 0;

    if (absDelta > 5)
        speed = 20;
    else if (absDelta > 3)
        speed = 15;
    else if (absDelta > 1)
        speed = 10;
    else if (absDelta > 0.5)
        speed = 5;
    else if (absDelta > 0.1)
        speed = 2;

    if (_delta < 0)
        return speed * -1;
    else
        return speed;
}

void DepthController::setEmergency(DepthController::EmergencyMode mode) {
    this->emergencyMode = mode;
    work();
}

void DepthController::serviceSyringe() {
    this->stopAll();
    this->ballast->clean();
}
