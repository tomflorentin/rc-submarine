//
// Created by tomfl on 5/9/2023.
//

#include <sstream>
#include "Status.hpp"

void Status::setLightStatus(uint8_t intensity) {
    std::lock_guard<std::mutex> guard(lck);
    this->lightStatus = intensity;
}

uint8_t Status::getLightStatus() {
    std::lock_guard<std::mutex> guard(lck);
    return this->lightStatus;
}

void Status::setTemperature(float temperature) {
    std::lock_guard<std::mutex> guard(lck);
    this->temperature = temperature;
}

float Status::getTemperature() {
    return 0;
}

void Status::setDepth(float _depth) {
    std::lock_guard<std::mutex> guard(lck);
    this->depth = _depth;

}

float Status::getDepth() {
    std::lock_guard<std::mutex> guard(lck);
    return this->depth;
}

void Status::setPower(uint8_t _power) {
    std::lock_guard<std::mutex> guard(lck);
    this->power = _power;
}

uint8_t Status::getPower() {
    std::lock_guard<std::mutex> guard(lck);
    return this->power;
}

void Status::setBallastFill(uint8_t _ballastFill) {
    std::lock_guard<std::mutex> guard(lck);
    this->ballastFill = _ballastFill;
}

uint8_t Status::getBallastFill() {
    std::lock_guard<std::mutex> guard(lck);
    return this->ballastFill;
}

void Status::setAlert(uint8_t _alert) {
    std::lock_guard<std::mutex> guard(lck);
    this->alert = _alert;
}

uint8_t Status::getAlert() {
    std::lock_guard<std::mutex> guard(lck);
    return this->alert;
}

void Status::setCameraAngle(uint8_t angle) {
   std::lock_guard<std::mutex> guard(lck);
    this->cameraAngle = angle;
}

uint8_t Status::getCameraAngle() {
    std::lock_guard<std::mutex> guard(lck);
    return this->cameraAngle;
}

void Status::setInsidePressure(float pressure) {
    std::lock_guard<std::mutex> guard(lck);
    this->insidePressure = pressure;
}

float Status::getInsidePressure() {
    std::lock_guard<std::mutex> guard(lck);
    return this->insidePressure;
}

void Status::setBatteryLevel(uint8_t level) {
    std::lock_guard<std::mutex> guard(lck);
    this->batteryLevel = level;

}

uint8_t Status::getBatteryLevel() {
    std::lock_guard<std::mutex> guard(lck);
    return this->batteryLevel;
}

std::string Status::getStatusText() {
    std::lock_guard<std::mutex> guard(lck);
    std::stringstream ss;

    ss << "Pronfondeur: " << this->depth << "m" << std::endl;
    ss << "Temperature interne: " << this->temperature << "C" << std::endl;
    ss << "Humidité interne: " << this->humidity << "%" << std::endl;
    ss << "Pression interne: " << this->insidePressure << "Bar" << std::endl;
    ss << "Niveau de batterie: " << (int)(this->batteryLevel/2.55) << "%" << std::endl;
    ss << "Etat du ballast: " << (int)(this->ballastFill/2.55) << "% (" << (int)((this->ballastFill /2.55) * 5)<<"ml)" << std::endl;
    ss << "Puissance de la lumiere: " << (int)(this->lightStatus/2.55) << "%" << std::endl;
    ss << "Angle de la camera: " << (this->cameraAngle) << "°" << std::endl;

    return ss.str();
}

void Status::setIsDiving(bool _diving) {
    std::lock_guard<std::mutex> guard(lck);
    this->isDiving = _diving;
}

bool Status::getIsDiving() {
    std::lock_guard<std::mutex> guard(lck);
    return this->isDiving;
}

void Status::setHumidity(float humidity) {
    std::lock_guard<std::mutex> guard(lck);
    this->humidity = humidity;
}

float Status::getHumidity() {
    std::lock_guard<std::mutex> guard(lck);
    return this->humidity;
}
