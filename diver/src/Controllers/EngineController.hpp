//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_ENGINECONTROLLER_HPP
#define EMBARQUE_ENGINECONTROLLER_HPP


#include <stdint.h>
#include "L298Controller.hpp"
#include "BTS7960Controller.hpp"

class EngineController : public ISetupable {
public:
    EngineController(uint8_t right_rpwm, uint8_t right_lpwm,
                     uint8_t left_rpwm, uint8_t left_lpwm);
    void setup() override;

    void move(uint8_t forward, uint8_t turn, uint8_t speedCoeff, uint8_t turnCoeff);
    void lock();
    void unlock();
    void work();

private:
    short targetRightSpeed = 0;
    short targetLeftSpeed = 0;
    short currentRightSpeed = 0;
    short currentLeftSpeed = 0;
    unsigned long lastSpeedChange = 0;
    unsigned long lastOrderTime = 0;
    bool isLocked = false;
    L298Controller rightMotor;
    L298Controller leftMotor;

    static short calcNewSpeed(short targetSpeed, short currentSpeed, unsigned long timeDiff);

};


#endif //EMBARQUE_ENGINECONTROLLER_HPP
