//
// Created by tomfl on 3/24/2023.
//

#ifndef EMBARQUE_SECURITYMONITOR_HPP
#define EMBARQUE_SECURITYMONITOR_HPP


#include "Security.hpp"
#include "RemoteControl/RemoteControl.hpp"
#include "Controllers/LedController.hpp"

#define SECURITY_CHECK_INTERVAL 500
#define NUMBER_OF_SECURITY_MODULES 8

class SecurityMonitor {
public:
    SecurityMonitor(RemoteControl *_remote,
                    DepthController *_depthController,
                    LedController *_ledController,
                    EngineController *_engineController);

    void addModule(Security *module);
    void work();

private:
    RemoteControl *remote;
    DepthController *depthController;
    LedController *ledController;
    EngineController *engineController;

    unsigned long lastCheck = 0;
    uint8_t nextModuleIndex = 0;
    Security *modules[NUMBER_OF_SECURITY_MODULES] = {};
};


#endif //EMBARQUE_SECURITYMONITOR_HPP
