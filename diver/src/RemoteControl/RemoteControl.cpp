//
// Created by tomfl on 3/19/2023.
//

#include <HardwareSerial.h>
#include "RemoteControl.hpp"
#include "Security/Security.hpp"
#include "func.hpp"

RemoteControl::RemoteControl(DepthController *_depth, EngineController *_engine, LedController *_led, CameraController *_camera)
    : ControlProtocol(), depthController(_depth), engineController(_engine), ledController(_led), cameraController(_camera)
{}

void RemoteControl::work(bool *isDiving) {
    Command cmd = this->receivePacket();

    if (cmd == Command::NO_COMMAND)
        return;
    if (cmd == Command::START_DIVE) {
        *isDiving = true;
        this->depthController->setEmergency(DepthController::EmergencyMode::NO_EMERGENCY);
    } else if (cmd == Command::END_DIVE) {
        *isDiving = false;
        this->ledController->right(false);
        this->ledController->left(false);
        this->depthController->setEmergency(DepthController::EmergencyMode::FLOAT);
    }


    switch (cmd) {
        case Command::ENGINE:
            this->handleEngine((EnginePayload*)recv_buffer);
            break;
        case Command::CAMERA:
            this->handleCamera((CameraPayload*)recv_buffer);
            break;
        case Command::LIGHTS:
            this->handleLights((LightsPayload*)recv_buffer);
            break;
        case Command::AUTO_DIVE:
            this->handleAutoDive(*(float *)recv_buffer);
            break;
        case Command::MANUAL_DIVE:
            this->handleManualDive(*(float *)recv_buffer);
            break;
        case Command::STABILIZE_DIVE:
            this->handleStabilize();
        case Command::SYRINGE_CLEAN:
            this->depthController->serviceSyringe();
            break;
        default:
            break;
    }
}


void RemoteControl::setup() {
    Serial.begin(9600);
    Serial.setTimeout(50);
}


void RemoteControl::sendAlert(Security::Result alert) {
    this->sendPacket(Command::ALERT, (uint8_t *)&alert, sizeof(Security::Result));
}

void RemoteControl::log(const char *str) {
    char *truncatedStr = NULL;
    size_t len = strlen(str);
    if (len > 50) {
        truncatedStr = static_cast<char *>(malloc(54));
        strncpy(truncatedStr, str, 50);
        strcat(truncatedStr, "...");
    }
    this->sendPacket(Command::LOG, (uint8_t*)( truncatedStr == nullptr ? str : truncatedStr), len);
    if (truncatedStr != nullptr)
        free(truncatedStr);
}

void RemoteControl::handleEngine(EnginePayload *payload) {
    this->engineController->move(payload->forward, payload->turn, payload->maxPower, payload->maxTurn);
}

void RemoteControl::handleCamera(CameraPayload *payload) {
    this->cameraController->setAngle(payload->vertical);
}

void RemoteControl::handleLights(LightsPayload *payload) {
    this->ledController->setBrightness(payload->intensity);
    this->ledController->left(payload->left);
    this->ledController->right(payload->right);
}

void RemoteControl::handleAutoDive(float depth) {
    this->depthController->setTargetDepth(depth);
}

void RemoteControl::handleStabilize() {
    this->depthController->stabilize();
}

void RemoteControl::handleManualDive(float cmPerSec) {
    this->depthController->setVerticalSpeed(cmPerSec);
}

void RemoteControl::log(String const &str) {
    this->log(str.c_str());
}
