//
// Created by tomfl on 3/19/2023.
//

#include <Arduino.h>
#include "UltrasonicSensor.hpp"

UltrasonicSensor::UltrasonicSensor(uint8_t _triggerPin, uint8_t _echoPin) : triggerPin(_triggerPin), echoPin(_echoPin){
}

float UltrasonicSensor::getDistance(int cacheMilleseconds) {
    unsigned long now = millis();
    if (this->lastDistanceTime + cacheMilleseconds < now) {
        this->lastDistance = readDistance();
        this->lastDistanceTime = now;
    }
    return this->lastDistance;
}

float UltrasonicSensor::readRawDistance() {
    this->triggerPin.write(false);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    this->triggerPin.write(true);
    delayMicroseconds(10);
    this->triggerPin.write(false);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    unsigned long duration = pulseIn(echoPin.getPin(), HIGH);
    // Calculating the distance
    return duration * 0.034 / 2.f;
}

float UltrasonicSensor::readDistance(signed char numberOfCalc) {
    float distance = 0;
    for (int i = 0; i < numberOfCalc; i++) {
        distance += readRawDistance();
    }
    return distance / (float)numberOfCalc;
}

void UltrasonicSensor::setup() {
    this->triggerPin.setup();
    this->echoPin.setup();
}


