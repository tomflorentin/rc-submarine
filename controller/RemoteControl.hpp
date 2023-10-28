//
// Created by tomfl on 3/28/2023.
//

#ifndef SURFACE_REMOTECONTROL_HPP
#define SURFACE_REMOTECONTROL_HPP


#include <cstdint>
#include "protocol.hpp"
#include "SerialPort.hpp"

class RemoteControl : public SerialPort {
public:
    explicit RemoteControl(char const *com_port);

    Command receivePacket();
    bool sendPacket(Command cmd, uint8_t *body, uint8_t bodySize);
    bool sendPacket(Command cmd);

    uint8_t recv_buffer[64];
    uint8_t send_buffer[64];

    uint8_t calculateChecksum(uint8_t const *buffer, uint8_t size, ::uint8_t initialValue = 0);
};


#endif //SURFACE_REMOTECONTROL_HPP
