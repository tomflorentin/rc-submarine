//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_BALLASTCONTROLLER_HPP
#define EMBARQUE_BALLASTCONTROLLER_HPP

#include "L298Controller.hpp"
#include "Sensors/UltrasonicSensor.hpp"
#include "ValveController.hpp"
#include "Interfaces/ISetupable.hpp"

class BallastController : public ISetupable {
public:
    BallastController(uint8_t _ultrasonicTriggerPin, uint8_t _ultrasonicEchoPin, uint8_t _motorPin1, uint8_t _motorPin2, uint8_t _fullLimitSwitchPin, uint8_t _emptyLimitSwitchPin, uint8_t _valvePin);

    void empty();
    void fill();
    void standby();
    void work();
    uint8_t getFillPercentage();

    void setup() override;
    void clean();
    signed char getIsMoving() const;
    signed char getIsCleaning() const;
private:
    UltrasonicSensor ultrasonicSensor;
    DigitalPinReader fullLimitSwitch;
    DigitalPinReader emptyLimitSwitch;
    L298Controller motorController;
    ValveController valveController;

    // Positive value -> filling
    // Negative value -> emptying
    signed isMoving = 0;

    enum CleaningProcess : signed char {
        NOT_CLEANING = 0,
        EMPTYING_OLD_WATER = -2,
        FILLING_CLEAR_WATER = 1,
        EMPTYING_CLEAR_WATER = -1
    };

    CleaningProcess isCleaning = NOT_CLEANING;
};


#endif //EMBARQUE_BALLASTCONTROLLER_HPP
