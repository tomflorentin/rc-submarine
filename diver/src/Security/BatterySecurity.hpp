//
// Created by tomfl on 3/24/2023.
//

#ifndef EMBARQUE_BATTERYSECURITY_HPP
#define EMBARQUE_BATTERYSECURITY_HPP


#include "Sensors/BatteryLevelSensor.hpp"
#include "Security.hpp"

class BatterySecurity : public Security {
public:
    explicit BatterySecurity(BatteryLevelSensor *_batterySensor);

protected:
    Alert checkSecurity() override;

private:
    BatteryLevelSensor *sensor;
};


#endif //EMBARQUE_BATTERYSECURITY_HPP
