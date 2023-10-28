//
// Created by tomfl on 4/20/2023.
//

#include "KeyboardHandler.hpp"

KeyboardHandler::KeyboardHandler(RemoteControl *_remoteControl, Status *_status) : remoteControl(_remoteControl),
                                                                                   status(_status) {
    this->enginePayload.turn = 127;
    this->enginePayload.forward = 127;
    this->enginePayload.maxPower = 70;
    this->enginePayload.maxTurn = 30;

    this->cameraPayload.active = 1;
    this->cameraPayload.vertical = 90;

    this->lightsPayload.left = false;
    this->lightsPayload.right = false;
    this->lightsPayload.intensity = 100;
}

void KeyboardHandler::handleKey(sf::Keyboard::Key key, bool shift) {
    if ((int)this->lastKey == (int)key && std::chrono::steady_clock::now() - this->lastKeyTime < std::chrono::milliseconds(100)) {
        return;
    }
    this->lastKey = (KeyboardCommand) key;
    this->lastKeyTime = std::chrono::steady_clock::now();

    switch (key) {
        case KeyboardCommand::FastForward:
            enginePayload.forward = 255;
            enginePayload.turn = 127;
            remoteControl->sendPacket(Command::ENGINE, (uint8_t *) &enginePayload, sizeof(EnginePayload));
            strcpy(this->commandText, ("Forward " + std::to_string(enginePayload.forward)).c_str());
            break;
        case KeyboardCommand::Forward:
            enginePayload.forward = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 255 : 190;
            enginePayload.turn = 127;
            remoteControl->sendPacket(Command::ENGINE, (uint8_t *) &enginePayload, sizeof(EnginePayload));
            strcpy(this->commandText, ("Forward " + std::to_string(enginePayload.forward)).c_str());
            break;
        case KeyboardCommand::Backward:
            enginePayload.forward = 70;
            enginePayload.turn = 127;
            remoteControl->sendPacket(Command::ENGINE, (uint8_t *) &enginePayload, sizeof(EnginePayload));
            strcpy(this->commandText, "Backward");
            break;
        case KeyboardCommand::Left:
            enginePayload.forward = 127;
            enginePayload.turn = 255;
            remoteControl->sendPacket(Command::ENGINE, (uint8_t *) &enginePayload, sizeof(EnginePayload));
            strcpy(this->commandText, "Left");
            break;
        case KeyboardCommand::Right:
            enginePayload.forward = 127;
            enginePayload.turn = 0;
            remoteControl->sendPacket(Command::ENGINE, (uint8_t *) &enginePayload, sizeof(EnginePayload));
            strcpy(this->commandText, "Right");
            break;
        case KeyboardCommand::Up:
            this->manualDivePayload = 3;
            this->remoteControl->sendPacket(Command::MANUAL_DIVE, (uint8_t *) &this->manualDivePayload,
                                            sizeof(float));
            strcpy(this->commandText, "Up");
            break;
        case KeyboardCommand::Down:
            this->manualDivePayload = -3;
            this->remoteControl->sendPacket(Command::MANUAL_DIVE, (uint8_t *) &this->manualDivePayload,
                                            sizeof(float));
            strcpy(this->commandText, "Down");
            break;
        case KeyboardCommand::LIGHT_UP:
            if (lightsPayload.intensity > 245) {
                lightsPayload.intensity = 245;
            }
            lightsPayload.intensity += 10;
            lightsPayload.right = true;
            lightsPayload.left = true;
            remoteControl->sendPacket(Command::LIGHTS, (uint8_t *) &lightsPayload, sizeof(LightsPayload));
            status->setLightStatus(lightsPayload.intensity);
            strcpy(this->commandText, "Light up");
            break;
        case KeyboardCommand::LIGHT_DOWN:
            if (lightsPayload.intensity < 10) {
                lightsPayload.intensity = 10;
            }
            lightsPayload.intensity -= 10;
            if (lightsPayload.intensity == 0) {
                lightsPayload.right = false;
                lightsPayload.left = false;
            } else {
                lightsPayload.right = true;
                lightsPayload.left = true;
            }
            remoteControl->sendPacket(Command::LIGHTS, (uint8_t *) &lightsPayload, sizeof(LightsPayload));
            status->setLightStatus(lightsPayload.intensity);
            strcpy(this->commandText, "Light down");
            break;
        case KeyboardCommand::CAMERA_UP:
            if (cameraPayload.vertical > 170) {
                cameraPayload.vertical = 170;
            }
            cameraPayload.vertical += 10;
            cameraPayload.active = 1;
            remoteControl->sendPacket(Command::CAMERA, (uint8_t *) &cameraPayload, sizeof(CameraPayload));
            status->setCameraAngle(cameraPayload.vertical);
            strcpy(this->commandText, "Camera up");
            break;
        case KeyboardCommand::CAMERA_DOWN:
            if (cameraPayload.vertical < 10) {
                cameraPayload.vertical = 10;
            }
            cameraPayload.vertical -= 10;
            cameraPayload.active = 1;
            remoteControl->sendPacket(Command::CAMERA, (uint8_t *) &cameraPayload, sizeof(CameraPayload));
            status->setCameraAngle(cameraPayload.vertical);
            strcpy(this->commandText, "Camera down");
            break;
        case KeyboardCommand::POWER_UP:
            if (enginePayload.maxPower > 245) {
                enginePayload.maxPower = 245;
            }
            enginePayload.maxPower += 10;
            remoteControl->sendPacket(Command::ENGINE, (uint8_t *) &enginePayload, sizeof(EnginePayload));
            status->setPower(enginePayload.maxPower);
            strcpy(this->commandText, "Power up");
            break;
        case KeyboardCommand::POWER_DOWN:
            if (enginePayload.maxPower < 10) {
                enginePayload.maxPower = 10;
            }
            enginePayload.maxPower -= 10;
            remoteControl->sendPacket(Command::ENGINE, (uint8_t *) &enginePayload, sizeof(EnginePayload));
            status->setPower(enginePayload.maxPower);
            strcpy(this->commandText, "Power down");
            break;
        case KeyboardCommand::START_STOP_DIVE: {
            auto newStatus = !this->status->getIsDiving();
            this->status->setIsDiving(newStatus);
            if (newStatus)
                this->remoteControl->sendPacket(Command::START_DIVE);
            else this->remoteControl->sendPacket(Command::END_DIVE);
            strcpy(this->commandText, "Start/stop dive");
        }
            break;
        case KeyboardCommand::SERVICE_SYRINGE:
            this->remoteControl->sendPacket(Command::SYRINGE_CLEAN);
            strcpy(this->commandText, "Service syringe");
            break;
        default:
            break;
    }
}

char const *KeyboardHandler::getCommandText() const {
    return this->commandText;
}
