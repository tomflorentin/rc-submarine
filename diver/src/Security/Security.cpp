//
// Created by tomfl on 3/24/2023.
//

#include "Security.hpp"

Security::Result Security::getStatus() {
    Alert status = this->checkSecurity();
    this->worstStatus |= status;

    Security::Result result;
    result.worstStatus = this->worstStatus;
    result.currentStatus = status;

    return result;
}

Security::Security() {

}
