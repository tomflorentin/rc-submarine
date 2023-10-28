//
// Created by tomfl on 3/24/2023.
//

#ifndef EMBARQUE_DEPTHSECURITY_HPP
#define EMBARQUE_DEPTHSECURITY_HPP


#include "Security.hpp"
#include "Sensors/DepthSensor.hpp"

class DepthSecurity : public Security {
public:
    explicit DepthSecurity(DepthSensor *_sensor);

protected:
    Alert checkSecurity() override;

private:
    DepthSensor *sensor;
};


#endif //EMBARQUE_DEPTHSECURITY_HPP
