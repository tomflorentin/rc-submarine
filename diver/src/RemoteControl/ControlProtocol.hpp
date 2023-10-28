//
// Created by tomfl on 3/26/2023.
//

#ifndef EMBARQUE_CONTROLPROTOCOL_HPP
#define EMBARQUE_CONTROLPROTOCOL_HPP


#include "protocol.hpp"

class ControlProtocol {
protected:
    ControlProtocol() = default;

    uint8_t calculateChecksum(uint8_t const *buffer, uint8_t size, ::uint8_t initialValue = 0);
    Command receivePacket();
    bool sendPacket(Command cmd, uint8_t *body, uint8_t bodySize);
    bool sendPacket(Command cmd);

    uint8_t send_buffer[64];
    uint8_t recv_buffer[64];
};


#endif //EMBARQUE_CONTROLPROTOCOL_HPP
