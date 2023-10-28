//
// Created by tomfl on 3/27/2023.
//

#include "SensorMonitor.hpp"

SensorMonitor::SensorMonitor(RemoteControl *_control, TemperatureSensor *_temperature, DepthSensor *_insidePressure,
                             BatteryLevelSensor *_batteryLevelSensor)
                             :
        control(_control),
        temperatureSensor(_temperature),
        insidePressure(_insidePressure),
        batteryLevelSensor(_batteryLevelSensor) {

}

void SensorMonitor::work() {
    unsigned long now = millis();

    // Exit if not 10000ms passed
    if (now - lastRead < 10000) {
        return;
    }
    lastRead = now;

    // Read sensors
    float temperature = this->temperatureSensor->getTemperature();
    float pressure = this->insidePressure->getPressure();
    uint8_t batteryLevel = this->batteryLevelSensor->getLevel();

    // Send data to remote
    control->sendConstant(Command::INSIDE_TEMPERATURE, temperature);
    control->sendConstant(Command::INSIDE_PRESSURE, pressure);
    control->sendConstant(Command::BATTERY, batteryLevel);
}
