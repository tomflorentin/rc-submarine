#include <Arduino.h>
#include "Controllers/BallastController.hpp"
#include "Controllers/EngineController.hpp"
#include "RemoteControl/protocol.hpp"
#include "Controllers/LedController.hpp"
#include "Controllers/DepthController.hpp"
#include "RemoteControl/RemoteControl.hpp"
#include "Security/BatterySecurity.hpp"
#include "Security/DepthSecurity.hpp"
#include "Security/WaterSecurity.hpp"
#include "Security/SecurityMonitor.hpp"
#include "Sensors/DHT.hpp"
#include "Sensors/SensorMonitor.hpp"
#include "func.hpp"
#include "Controllers/CameraController.hpp"
#include "Sensors/TemperatureSensor.hpp"
#include "PowerManager.hpp"
//
//// Sensors
DepthSensor outsideDepthSensor = DepthSensor(11);
DepthSensor insideDepthSensor = DepthSensor(12);
BatteryLevelSensor batteryLevel = BatteryLevelSensor(1);
////TemperatureSensor dhtSensor = TemperatureSensor(30);
DHT dhtSensor = DHT(30);
//
// Main controllers

CameraController camera = CameraController(11);

BallastController ballastController = BallastController(1,
                                                        2,
                                                        2,
                                                        3,
                                                        22,
                                                        24,
                                                        26);

DepthController depthController = DepthController(&ballastController, &outsideDepthSensor);

EngineController engine = EngineController(5,
                                           6,
                                           3,
                                           4,
                                           0,
                                           0,
                                           0,
                                           0);

LedController led = LedController(3, 25);

RemoteControl remote = RemoteControl(&depthController, &engine, &led, &camera);

SensorMonitor sensorMonitor = SensorMonitor(&remote, &dhtSensor, &insideDepthSensor, &batteryLevel);
//
//// Security
BatterySecurity batterySecurity = BatterySecurity(&batteryLevel);
DepthSecurity depthSecurity = DepthSecurity(&outsideDepthSensor);
WaterSecurity waterSecurity = WaterSecurity(1, 2, 3, 4);

SecurityMonitor securityMonitor = SecurityMonitor(&remote, &depthController, &led, &engine);
PowerManager powerManager = PowerManager();

unsigned long elapsed = 0;

void setup() {
    randomSeed(analogRead(0));
    ballastController.setup();
    engine.setup();
//    led.setup();
    camera.setup();
//    outsideDepthSensor.setup();
//    insideDepthSensor.setup();
//    batteryLevel.setup();
      remote.setup();
//    waterSecurity.setup();

//    securityMonitor.addModule(&batterySecurity);
//    securityMonitor.addModule(&depthSecurity);
//    securityMonitor.addModule(&waterSecurity);

    setupLogger(&remote);

    dhtSensor.begin();

    // Camera power
    powerManager.drawPower(12345, 20);

    // Arduino power
    powerManager.drawPower(6789, 5);
}

bool isDiving = false;

int i = 20;

void loop() {

    sensorMonitor.work();
    remote.work(&isDiving);
    depthController.work();
    ballastController.work();
    engine.work();
    powerManager.work();
//
    if (isDiving) {
        securityMonitor.work();
    }

//    elapsed += millis();
//    if (elapsed > 35000) {
//        engine.move(0, 0, 0, 0);
//        elapsed = 0;
//    } else if (elapsed > 30000) {
//        engine.move(255, 0, 255, 255);
//    } else if (elapsed > 25000) {
//        engine.move(200, 0, 255, 255);
//    } else if (elapsed > 20000) {
//        engine.move(150, 0, 255, 255);
//    } else if (elapsed > 1500) {
//        engine.move(100, 0, 255, 255);
//    } else if (elapsed > 10000) {
//        engine.move(50, 0, 255, 255);
//    } else if (elapsed > 5000) {
//        engine.move(0, 0, 255, 255);
//    }
}