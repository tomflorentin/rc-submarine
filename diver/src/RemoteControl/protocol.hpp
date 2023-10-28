//
// Created by tomfl on 3/19/2023.
//

#ifndef EMBARQUE_PROTOCOL_HPP
#define EMBARQUE_PROTOCOL_HPP

#include <stdint.h>

enum class Command : unsigned char {
    NO_COMMAND = 0,

    // Requests
    START_DIVE = 1,
    END_DIVE = 2,
    ENGINE = 5,
    CAMERA = 6,
    LIGHTS = 7,
    AUTO_DIVE = 8,
    MANUAL_DIVE = 9,
    STABILIZE_DIVE = 10,
    RESET_ALERTS = 11,
    SYRINGE_CLEAN = 12,

    // Responses
    INSIDE_TEMPERATURE = 101,
    INSIDE_PRESSURE = 102,
    INSIDE_HUMIDITY = 103,
    DEPTH = 104,
    BALLAST_FILL = 105,
    BATTERY = 106,
    ALERT = 107,

    // Ping, logs
    CHECK_PING = 250,
    CHECK_PONG = 251,
    LOG = 252,

    HEADER1 = 151,
    HEADER2 = 242
};

struct EnginePayload {
    uint8_t maxPower;
    uint8_t maxTurn;
    uint8_t forward;
    uint8_t turn;
};

struct CameraPayload {
    uint8_t active;
    uint8_t vertical;
};

struct LightsPayload {
    bool right;
    bool left;
    uint8_t intensity;
};

template<class T>
bool enumHas(T base, T search) {
    return (base & search) == search;
}

template<class T>
T enumCombine(T base, T add) {
    return static_cast<T>(base | add);
}

enum Alert : unsigned short {
    None = 0,
    WaterFront = 1,
    WaterBack = 2,
    WaterSeringueGasket = 4,
    WaterSeringueOut = 16,
    Overheat = 32,
    PressureFailure = 64,
    LowBattery = 128,
    MaxDepth = 256
};

enum Combinable {
    ViewPatient = 0,
    CreatePatient = 1,
    EditPatientInfos = 2,
    EditPatientProtocol = 4,
    SendDirectNotification = 16,
    AnswerSurvey = 32,
    PatientDocuments = 64,
    WriteReport = 128,
    // 256,
    // 512,
    // 1024,
    // 2048,
    // 4096,
    // 8192,
    // 16384,
    // 32768,
    // 65536,
    // 131072,
    // 262144,
    // 524288,
    // 1048576,
    // 2097152,
    // 4194304,
    // 8388608,
    // 16777216,
    // 33554432,
    // 67108864,
    // 134217728,
    // 268435456,
    // 536870912,
    // 1073741824,
    // 2147483648,
    All = 2147483647
};

#endif //EMBARQUE_PROTOCOL_HPP
