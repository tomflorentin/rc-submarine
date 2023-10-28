//
// Created by tomfl on 5/16/2023.
//

#ifndef EMBARQUE_IPOWERMONITORABLE_HPP
#define EMBARQUE_IPOWERMONITORABLE_HPP


#include <stdint.h>

class IPowerMonitorable {
protected:
    explicit IPowerMonitorable(unsigned short _maxWatts);

    void drawPower(uint8_t power);
private:
    unsigned short maxWatts;
    int id;
};


#endif //EMBARQUE_IPOWERMONITORABLE_HPP
