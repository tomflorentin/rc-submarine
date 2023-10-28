//
// Created by tomfl on 3/26/2023.
//

#include <HardwareSerial.h>
#include "ControlProtocol.hpp"
#include "func.hpp"


bool ControlProtocol::sendPacket(Command cmd) {
    return this->sendPacket(cmd, nullptr, 0);
}

bool ControlProtocol::sendPacket(Command cmd, uint8_t *body, uint8_t bodySize) {
    unsigned short packetSize = 0;
    memset(send_buffer, 0, sizeof (this->send_buffer));
    send_buffer[packetSize++] = (uint8_t)Command::HEADER1;
    send_buffer[packetSize++] = (uint8_t)Command::HEADER2;
    send_buffer[packetSize++] = (uint8_t)cmd;

    this->send_buffer[packetSize++] = bodySize;
    if (bodySize != 0 && body != nullptr) {
        memcpy(((uint8_t *)((uint8_t*)this->send_buffer) + packetSize), body, bodySize);
        packetSize += bodySize;
    }
    this->send_buffer[packetSize] = this->calculateChecksum(this->send_buffer, packetSize);
    packetSize++;
    return Serial.write(this->send_buffer, packetSize) == packetSize;
}


Command ControlProtocol::receivePacket() {
    uint8_t checksum = 0;

    // Headers check
    uint8_t header1;
    if (Serial.readBytes((uint8_t *)&header1, sizeof(uint8_t)) != sizeof (uint8_t)) {
        return Command::NO_COMMAND;
    }
    if (header1 != (uint8_t)Command::HEADER1) {
        return Command::NO_COMMAND;
    }

    uint8_t header2;
    if (Serial.readBytes((uint8_t *)&header2, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;
    if (header2 != (uint8_t)Command::HEADER2) {
        return Command::NO_COMMAND;
    }

    checksum += (uint8_t)header1;
    checksum += (uint8_t)header2;


    // Get command
    uint8_t command;
    if (Serial.readBytes((uint8_t *)&command, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;

    checksum += (uint8_t)command;


    // Read body
    uint8_t bodySize;
    if (Serial.readBytes((uint8_t *)&bodySize, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;

    checksum += (uint8_t)bodySize;

    if (bodySize > 0) {
        memset(this->recv_buffer, 0, sizeof(recv_buffer));

        if (Serial.readBytes((uint8_t *) this->recv_buffer, bodySize) != bodySize)
            return Command::NO_COMMAND;

        checksum = this->calculateChecksum(this->recv_buffer, bodySize, checksum);
    }

    uint8_t receivedChecksum;
    if (Serial.readBytes((uint8_t *)&receivedChecksum, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;

    if (checksum != receivedChecksum) {
        Log("Checksum is not correct");
        return Command::NO_COMMAND;
    }

    return (Command)command;
}

uint8_t ControlProtocol::calculateChecksum(uint8_t const *_buffer, uint8_t size, uint8_t init) {
    uint8_t checksum = init;
    for (int i = 0; i < size; i++) {
        checksum += _buffer[i];
    }
    return checksum;
}
