//
// Created by tomfl on 5/16/2023.
//

#include <new>
#include "IPowerMonitorable.hpp"
#include "PowerManager.hpp"

IPowerMonitorable::IPowerMonitorable(unsigned short _maxWatts) : maxWatts(_maxWatts) {
    this->id = random() % INT32_MAX;
}

void IPowerMonitorable::drawPower(uint8_t power) {
    PowerManager::instance->drawPower(this->id, (float) (this->maxWatts * ((float) power / 255.f)));
}
