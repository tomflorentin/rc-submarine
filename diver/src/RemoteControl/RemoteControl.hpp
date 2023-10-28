//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_REMOTECONTROL_HPP
#define EMBARQUE_REMOTECONTROL_HPP


#include "Controllers/EngineController.hpp"
#include "Controllers/DepthController.hpp"
#include "Controllers/LedController.hpp"
#include "protocol.hpp"
#include "Security/Security.hpp"
#include "ControlProtocol.hpp"
#include "Controllers/CameraController.hpp"

class RemoteControl : public ISetupable, public ControlProtocol {
public:
    RemoteControl(DepthController *_depth, EngineController *_engine, LedController *_led, CameraController *_camera);
    void work(bool *isDiving);

    void setup() override;

    void sendAlert(Security::Result alert);
    void log(char const *str);
    void log(String const &str);


    // Templates
    template<class T>void sendConstant(Command cmd, T value) {
        this->sendPacket(cmd, (uint8_t*)&value, sizeof(T));
    }

private:
    // Handlers
    void handleEngine(EnginePayload *payload);
    void handleCamera(CameraPayload *payload);
    void handleLights(LightsPayload *payload);
    void handleAutoDive(float depth);
    void handleStabilize();
    void handleManualDive(float cmPerSec);

    DepthController *depthController;
    EngineController *engineController;
    LedController *ledController;
    CameraController *cameraController;
};


#endif //EMBARQUE_REMOTECONTROL_HPP
