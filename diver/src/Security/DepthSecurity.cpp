//
// Created by tomfl on 3/24/2023.
//

#include "DepthSecurity.hpp"

DepthSecurity::DepthSecurity(DepthSensor *_sensor) : sensor(_sensor) {
}

Alert DepthSecurity::checkSecurity() {
    float depth = sensor->getDepth();
    if (depth > 15)
        return Alert::MaxDepth;
    return Alert::None;
}
