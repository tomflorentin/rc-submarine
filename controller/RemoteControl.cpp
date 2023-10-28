//
// Created by tomfl on 3/28/2023.
//

#include <cstring>
#include <iostream>
#include "RemoteControl.hpp"

RemoteControl::RemoteControl(char const *com_port) : SerialPort(com_port, 9600) {
}


bool RemoteControl::sendPacket(Command cmd) {
    return this->sendPacket(cmd, nullptr, 0);
}

bool RemoteControl::sendPacket(Command cmd, uint8_t *body, uint8_t bodySize) {
    unsigned short packetSize = 0;
    uint8_t checksum = 0;

    memset(send_buffer, 0, sizeof (this->send_buffer));
    send_buffer[packetSize++] = (uint8_t)Command::HEADER1;
    checksum += (uint8_t)Command::HEADER1;
    send_buffer[packetSize++] = (uint8_t)Command::HEADER2;
    checksum += (uint8_t)Command::HEADER2;
    send_buffer[packetSize++] = (uint8_t)cmd;
    checksum += (uint8_t)cmd;

    this->send_buffer[packetSize++] = bodySize;
    if (bodySize != 0 && body != nullptr) {
        memcpy(((uint8_t *)((uint8_t*)this->send_buffer) + packetSize), body, bodySize);
        packetSize += bodySize;
        checksum += bodySize;
        checksum = this->send_buffer[packetSize] = this->calculateChecksum(body, bodySize, checksum);
    }

    this->send_buffer[packetSize++] = checksum;

    unsigned short sentSize = this->writeSerialPort((char const*)this->send_buffer, packetSize);
    if (sentSize != packetSize)
        std::cout << "Error sending packet" << std::endl;
    else
    return sentSize == packetSize;
}


Command RemoteControl::receivePacket() {
    ::uint8_t checksum = 0;

    // Headers check
    Command header1;
    if (this->readSerialPort((char const *)&header1, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;
    if (header1 != Command::HEADER1)
        return Command::NO_COMMAND;

    Command header2;
    if (this->readSerialPort((char const *)&header2, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;
    if (header2 != Command::HEADER2)
        return Command::NO_COMMAND;

    checksum += (std::uint8_t)header1;
    checksum += (std::uint8_t)header2;

    // Get command
    Command command;
    if (this->readSerialPort((char const *)&command, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;

    checksum += (std::uint8_t)command;

    // Read body
    uint8_t bodySize;
    if (this->readSerialPort((char const *)&bodySize, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;

    checksum += bodySize;

    if (bodySize > 0) {
        memset(this->recv_buffer, 0, sizeof(recv_buffer));
        if (this->readSerialPort((char const *) this->recv_buffer, bodySize) != bodySize)
            return Command::NO_COMMAND;


        checksum = this->calculateChecksum((uint8_t *) this->recv_buffer, bodySize, checksum);
    }

    // Read recvChecksum
    uint8_t recvChecksum;
    if (this->readSerialPort((char const *)&recvChecksum, sizeof(uint8_t)) != sizeof (uint8_t))
        return Command::NO_COMMAND;

    if (recvChecksum != checksum) {
        std::cout << "Checksum error" << std::endl;
        return Command::NO_COMMAND;
    }

    return command;
}

uint8_t RemoteControl::calculateChecksum(uint8_t const *_buffer, uint8_t size, uint8_t init) {
    uint8_t checksum = init;
    for (int i = 0; i < size; i++) {
        checksum += _buffer[i];
    }
    return checksum;
}

