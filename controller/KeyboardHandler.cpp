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


    // Construct the keymap string
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::Forward) + " : Forward\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::Backward) + " : Backward\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::Left) + " : Left\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::Right) + " : Right\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::Up) + " : Up\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::Down) + " : Down\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::LIGHT_UP) + " : Light up\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::LIGHT_DOWN) + " : Light down\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::CAMERA_UP) + " : Camera up\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::CAMERA_DOWN) + " : Camera down\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::POWER_UP) + " : Power up\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::POWER_DOWN) + " : Power down\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::START_STOP_DIVE) + " : Start/stop dive\n";
    this->keymapText += this->mapSfKeyToStr(KeyboardCommand::SERVICE_SYRINGE) + " : Service syringe\n";
}

void KeyboardHandler::handleKey(sf::Keyboard::Key key, bool shift) {
    if ((int) this->lastKey == (int) key &&
        std::chrono::steady_clock::now() - this->lastKeyTime < std::chrono::milliseconds(100)) {
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

char const *KeyboardHandler::getKeymapText() const {
    return this->keymapText.c_str();
}

std::string KeyboardHandler::mapSfKeyToStr(KeyboardCommand key) {
    switch ((sf::Keyboard::Key) key) {
        case sf::Keyboard::Unknown:
            return "Unknown";
        case sf::Keyboard::A:
            return "A";
        case sf::Keyboard::B:
            return "B";
        case sf::Keyboard::C:
            return "C";
        case sf::Keyboard::D:
            return "D";
        case sf::Keyboard::E:
            return "E";
        case sf::Keyboard::F:
            return "F";
        case sf::Keyboard::G:
            return "G";
        case sf::Keyboard::H:
            return "H";
        case sf::Keyboard::I:
            return "I";
        case sf::Keyboard::J:
            return "J";
        case sf::Keyboard::K:
            return "K";
        case sf::Keyboard::L:
            return "L";
        case sf::Keyboard::M:
            return "M";
        case sf::Keyboard::N:
            return "N";
        case sf::Keyboard::O:
            return "O";

        case sf::Keyboard::P:
            return "P";
        case sf::Keyboard::Q:
            return "Q";
        case sf::Keyboard::R:
            return "R";
        case sf::Keyboard::S:
            return "S";
        case sf::Keyboard::T:
            return "T";
        case sf::Keyboard::U:
            return "U";
        case sf::Keyboard::V:
            return "V";
        case sf::Keyboard::W:
            return "W";
        case sf::Keyboard::X:
            return "X";
        case sf::Keyboard::Y:
            return "Y";
        case sf::Keyboard::Z:
            return "Z";
        case sf::Keyboard::Num0:
            return "Num0";
        case sf::Keyboard::Num1:
            return "Num1";
        case sf::Keyboard::Num2:
            return "Num2";
        case sf::Keyboard::Num3:
            return "Num3";
        case sf::Keyboard::Num4:
            return "Num4";
        case sf::Keyboard::Num5:
            return "Num5";
        case sf::Keyboard::Num6:
            return "Num6";
        case sf::Keyboard::Num7:
            return "Num7";
        case sf::Keyboard::Num8:
            return "Num8";
        case sf::Keyboard::Num9:
            return "Num9";
        case sf::Keyboard::Escape:
            return "Escape";
        case sf::Keyboard::LControl:
            return "LControl";
        case sf::Keyboard::LShift:
            return "LShift";
        case sf::Keyboard::LAlt:
            return "LAlt";
        case sf::Keyboard::LSystem:
            return "LSystem";
        case sf::Keyboard::RControl:
            return "RControl";
        case sf::Keyboard::RShift:
            return "RShift";
        case sf::Keyboard::RAlt:
            return "RAlt";
        case sf::Keyboard::RSystem:
            return "RSystem";
        case sf::Keyboard::Menu:
            return "Menu";
        case sf::Keyboard::LBracket:
            return "LBracket";
        case sf::Keyboard::RBracket:
            return "RBracket";
        case sf::Keyboard::SemiColon:
            return "SemiColon";
        case sf::Keyboard::Comma:
            return "Comma";
        case sf::Keyboard::Period:
            return "Period";
        case sf::Keyboard::Quote:
            return "Quote";
        case sf::Keyboard::Slash:
            return "Slash";
        case sf::Keyboard::BackSlash:
            return "BackSlash";
        case sf::Keyboard::Tilde:
            return "Tilde";
        case sf::Keyboard::Tab:
            return "Tab";
        case sf::Keyboard::Enter:
            return "Enter";
        default:
            return "Unknown";
    }
}
