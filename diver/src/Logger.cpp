//
// Created by tomfl on 3/27/2023.
//

#include "func.hpp"
#include "RemoteControl/RemoteControl.hpp"

static RemoteControl *control;

void setupLogger(RemoteControl *_control) {
    control = _control;
}

void Log(const char *message) {
    control->log(message);
}

void Log(String const &message) {
    control->log(message);
}