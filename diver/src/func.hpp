//
// Created by tomfl on 3/27/2023.
//

#ifndef EMBARQUE_FUNC_HPP
#define EMBARQUE_FUNC_HPP


#include <Arduino.h>
#include "RemoteControl/RemoteControl.hpp"

void setupLogger(RemoteControl *_control);

void Log(const char *message);

void Log(String const &message);

#endif //EMBARQUE_FUNC_HPP
