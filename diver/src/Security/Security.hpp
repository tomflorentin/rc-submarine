//
// Created by tomfl on 3/24/2023.
//

#ifndef EMBARQUE_SECURITY_HPP
#define EMBARQUE_SECURITY_HPP


#include <stdint.h>
#include "RemoteControl/protocol.hpp"

class Security {
public:
    struct Result {
        Alert worstStatus = Alert::None;
        Alert currentStatus = Alert::None;
    };

    Result getStatus();

protected:
    virtual Alert checkSecurity() = 0;
    Security();

private:
    Alert worstStatus = Alert::None;
};


#endif //EMBARQUE_SECURITY_HPP
