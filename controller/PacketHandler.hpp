//
// Created by tomfl on 5/9/2023.
//

#ifndef SURFACE_PACKETHANDLER_HPP
#define SURFACE_PACKETHANDLER_HPP


#include "Status.hpp"
#include "protocol.hpp"

class PacketHandler {
public:
    explicit PacketHandler(Status *_status);
    void handlePacket(Command command, uint8_t const *buffer);

private:
    Status *status;
};


#endif //SURFACE_PACKETHANDLER_HPP
