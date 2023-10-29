//
// Created by tomfl on 4/20/2023.
//

#ifndef SURFACE_KEYBOARDHANDLER_HPP
#define SURFACE_KEYBOARDHANDLER_HPP

#include <SFML/Window/Keyboard.hpp>
#include "RemoteControl.hpp"
#include "Status.hpp"

enum KeyboardCommand : int {
    NONE = sf::Keyboard::Key::Unknown,
    Forward = sf::Keyboard::Key::Z,
    FastForward = sf::Keyboard::Key::LShift,
    Backward = sf::Keyboard::Key::S,
    Left = sf::Keyboard::Key::Q,
    Right = sf::Keyboard::Key::D,
    Up = sf::Keyboard::Key::Tab,
    Down = sf::Keyboard::Key::LControl,
    LIGHT_UP = sf::Keyboard::Key::I,
    LIGHT_DOWN = sf::Keyboard::Key::K,
    CAMERA_UP = sf::Keyboard::Key::O,
    CAMERA_DOWN = sf::Keyboard::Key::L,
    POWER_UP = sf::Keyboard::Key::R,
    POWER_DOWN = sf::Keyboard::Key::F,
    START_STOP_DIVE = sf::Keyboard::Key::Enter,
    SERVICE_SYRINGE = sf::Keyboard::Key::M,
};

class KeyboardHandler {
public:
    explicit KeyboardHandler(RemoteControl *_remoteControl, Status *_status);

    void handleKey(sf::Keyboard::Key key, bool shift);
    char const *getCommandText() const;
    char const *getKeymapText() const;

private:
    RemoteControl *remoteControl;
    Status *status;

    EnginePayload enginePayload;
    CameraPayload cameraPayload;
    LightsPayload lightsPayload;
    float manualDivePayload;

    char commandText[1024] = {0};
    std::string keymapText = "Keymap reminder :\n";

    std::chrono::steady_clock::time_point lastKeyTime = std::chrono::steady_clock::now();
    KeyboardCommand lastKey = KeyboardCommand::NONE;

    std::string mapSfKeyToStr(KeyboardCommand key);
};


#endif //SURFACE_KEYBOARDHANDLER_HPP
