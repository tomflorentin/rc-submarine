//
// Created by tomfl on 3/19/2023.
//

#include "BallastController.hpp"
#include "func.hpp"

const int MAX_DISTANCE = 20;
const int MIN_DISTANCE = 5;

BallastController::BallastController(uint8_t _ultrasonicTriggerPin, uint8_t _ultrasonicEchoPin, uint8_t _motorPin1,
                                     uint8_t _motorPin2, uint8_t _fullLimitSwitchPin, uint8_t _emptyLimitSwitchPin,
                                     uint8_t _valvePin)
        : ultrasonicSensor(_ultrasonicTriggerPin, _ultrasonicEchoPin),
          fullLimitSwitch(_fullLimitSwitchPin), emptyLimitSwitch(_emptyLimitSwitchPin),
          motorController(_motorPin1, _motorPin2, 5), valveController(_valvePin) {

}

void BallastController::empty() {
    bool isEmpty = this->emptyLimitSwitch.read();
    Log("Start emptying " + String(isEmpty));
    if (!isEmpty) {
        this->isMoving = -1;
        this->valveController.open();
        this->motorController.forward(255);
    } else {
        this->standby();
        Log("Standby because empty");
    }
}


void BallastController::fill() {
    bool isFull = this->fullLimitSwitch.read();
    Log("Start filling " + String(isFull));
    if (!isFull) {
        this->isMoving = 1;
        this->valveController.open();
        this->motorController.backward(255);
    } else {
        Log("Standby because full");
        this->standby();
    }
}

void BallastController::standby() {
    Log("Standby CALLED");
    this->isMoving = 0;
    this->valveController.close();
    this->motorController.standby();
}

void BallastController::work() {
    if (!isMoving) {
        return;
    }
    bool isEmpty = this->emptyLimitSwitch.read();
    bool isFull = this->fullLimitSwitch.read();

    Log("IsCleaning: " + String(this->isCleaning) + " isEmpty: " + String(isEmpty) + " isFull: " + String(isFull));

    if (this->isCleaning == CleaningProcess::EMPTYING_OLD_WATER && isEmpty) {
        Log("Filling clear water");
        this->isCleaning = CleaningProcess::FILLING_CLEAR_WATER;
        this->fill();
        return;
    }
    if (this->isCleaning == CleaningProcess::FILLING_CLEAR_WATER && isFull) {
        Log("Emptying clear water");
        this->isCleaning = CleaningProcess::EMPTYING_CLEAR_WATER;
        this->empty();
        return;
    }
    if (this->isCleaning == CleaningProcess::EMPTYING_CLEAR_WATER && isEmpty) {
        Log("Cleaning process finished");
        this->isCleaning = CleaningProcess::NOT_CLEANING;
        this->standby();
        return;
    }

    if (this->isCleaning == CleaningProcess::NOT_CLEANING && (isEmpty || isFull)) {
        this->standby();
    }
}

signed char BallastController::getIsMoving() const {
    return this->isMoving;
}

void BallastController::setup() {
    this->motorController.setup();
    this->valveController.setup();
    this->ultrasonicSensor.setup();
}

uint8_t BallastController::getFillPercentage() {
    if (fullLimitSwitch.read()) {
        return 100;
    }
    if (emptyLimitSwitch.read()) {
        return 0;
    }

    float distance = ultrasonicSensor.getDistance(300);
    int percent = (int) ((distance - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE) * 100.f);
    return percent;
}

void BallastController::clean() {
    Log("Starting cleaning process");
    if (this->emptyLimitSwitch.read()) {
        this->fill();
        this->isCleaning = FILLING_CLEAR_WATER;
    } else {
        this->empty();
        this->isCleaning = EMPTYING_OLD_WATER;
    }
}

signed char BallastController::getIsCleaning() const {
    return this->isCleaning;
}
