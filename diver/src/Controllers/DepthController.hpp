//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_DEPTHCONTROLLER_HPP
#define EMBARQUE_DEPTHCONTROLLER_HPP


#include "BallastController.hpp"
#include "PinReader/AnalogPinReader.hpp"
#include "Sensors/DepthSensor.hpp"

#define NUMBER_OF_LAST_DEPTHS 16

class DepthController {
public:
    enum VerticalSpeedCorrection {
        NO_CORRECTION,
        INCREASE,
        DECREASE,
    };

    enum EmergencyMode {
        NO_EMERGENCY,
        FLOAT,
        SEAL
    };

    DepthController(BallastController *_ballast, DepthSensor *_depthSensor);

    void work();
    void setTargetDepth(float _depth);
    void stopAll();

    void setVerticalSpeed(float _speed);
    void stabilize();
    float getVerticalSpeed();
    void setEmergency(EmergencyMode mode);
    void serviceSyringe();


private:
    float getDesiredSpeedForDelta(float _delta);
    void storeDepth();

    EmergencyMode emergencyMode = EmergencyMode::NO_EMERGENCY;
    bool isTargetingSpeed = false;
    float targetSpeed = 0;
    bool isTargetingDepth = false;
    float targetDepth = 0;
    unsigned int lastManualDiveOrderTime = 0;
    BallastController *ballast;
    DepthSensor *depthSensor;

    float verticalSpeed = 0;
    float lastDepths[NUMBER_OF_LAST_DEPTHS]{};
    unsigned long lastDepthsTime[NUMBER_OF_LAST_DEPTHS]{};
    unsigned short lastDepthsIndex = 0;
};


#endif //EMBARQUE_DEPTHCONTROLLER_HPP
