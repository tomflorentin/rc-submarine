//
// Created by tomfl on 5/9/2023.
//

#include <iostream>
#include "PacketHandler.hpp"

PacketHandler::PacketHandler(Status *_status) : status(_status) {

}

void PacketHandler::handlePacket(Command command, uint8_t const *buffer) {
    switch (command) {
        case Command::INSIDE_TEMPERATURE:
            status->setTemperature(*(float*)buffer);
            break;
        case Command::INSIDE_HUMIDITY:
            status->setHumidity(*(float*)buffer);
            break;
        case Command::INSIDE_PRESSURE:
            status->setInsidePressure(*(float*)buffer);
            break;
        case Command::DEPTH:
            status->setDepth(*(float*)buffer);
            break;
        case Command::BALLAST_FILL:
            status->setBallastFill(*buffer);
            break;
        case Command::BATTERY:
            status->setBatteryLevel(*buffer);
            break;
        case Command::LOG:
            std::cout << "Log: " << (char*)buffer << std::endl;
            break;
        default:
            std::cout << "Unknown command: " << (int)command << std::endl;
    }
}
