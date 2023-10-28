//
// Created by tomfl on 3/24/2023.
//

#include <string.h>
#include <Arduino.h>
#include "SecurityMonitor.hpp"
#include "func.hpp"

SecurityMonitor::SecurityMonitor(RemoteControl *_remote,
                                 DepthController *_depthController,
                                 LedController *_ledController,
                                 EngineController *_engineController)
                               : remote(_remote),
                               depthController(_depthController),
                               ledController(_ledController),
                               engineController(_engineController)
                               {
    memset(this->modules, 0, sizeof(Security*) * NUMBER_OF_SECURITY_MODULES);
}

void SecurityMonitor::addModule(Security *module) {
    if (this->nextModuleIndex >= NUMBER_OF_SECURITY_MODULES) {
        Log("Not adding a security module");
        return;
    }

    this->modules[this->nextModuleIndex] = module;
    this->nextModuleIndex += 1;
}

void SecurityMonitor::work() {
    unsigned long now = millis();
    if (now - this->lastCheck < SECURITY_CHECK_INTERVAL) {
        return;
    }
    this->lastCheck = now;

    Security::Result globalStatus;
    for (int i = 0; i < this->nextModuleIndex; i++) {
        if (this->modules[i] == nullptr)
            continue;

        Security::Result moduleStatus = this->modules[i]->getStatus();
        globalStatus.currentStatus = enumCombine(globalStatus.currentStatus,moduleStatus.currentStatus);
        globalStatus.worstStatus = enumCombine(globalStatus.worstStatus, moduleStatus.worstStatus);
    }

    if (globalStatus.worstStatus == 0 && globalStatus.currentStatus == 0) {
        return;
    }

    // -----------------
    // CRITIAL PROBLEMS
    // -----------------

    // Body water leak
    if (enumHas(globalStatus.worstStatus, Alert::WaterBack) || enumHas(globalStatus.worstStatus, Alert::WaterFront)) {
        this->depthController->setEmergency(DepthController::EmergencyMode::FLOAT);
    }

    // Seringue water leak
    if (enumHas(globalStatus.worstStatus, Alert::WaterSeringueGasket) || enumHas(globalStatus.worstStatus, Alert::WaterSeringueOut)) {
        this->depthController->setEmergency(DepthController::SEAL);
    }

    // Pressure failure
    if (enumHas(globalStatus.worstStatus, Alert::PressureFailure)) {
        this->depthController->setEmergency(DepthController::EmergencyMode::FLOAT);
    }


    // -----------------
    // MINOR PROBLEMS
    // -----------------

    // Overheat
    if (enumHas(globalStatus.currentStatus, Alert::Overheat)) {
        this->engineController->lock();
        this->ledController->left(false);
        this->ledController->right(false);
        this->depthController->stabilize();
    }
    // Overheat finished
    if (enumHas(globalStatus.worstStatus, Alert::Overheat) && !enumHas(globalStatus.currentStatus, Alert::Overheat)) {
        this->engineController->unlock();
    }

    // Low battery
    if (enumHas(globalStatus.currentStatus, Alert::LowBattery)) {
        // Shutdown lights
    }

    if (enumHas(globalStatus.currentStatus, Alert::MaxDepth)) {
        this->depthController->setEmergency(DepthController::EmergencyMode::FLOAT);
    }




}
