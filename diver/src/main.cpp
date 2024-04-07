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
                                                        5,
                                                        6,
                                                        13,
                                                        12,
                                                        11);

DepthController depthController = DepthController(&ballastController, &outsideDepthSensor);

EngineController engine = EngineController(5,
                                           6,
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
//    engine.setup();
//    led.setup();
//    camera.setup();
//    outsideDepthSensor.setup();
//    insideDepthSensor.setup();
//    batteryLevel.setup();
      remote.setup();
//    waterSecurity.setup();

//    securityMonitor.addModule(&batterySecurity);
//    securityMonitor.addModule(&depthSecurity);
//    securityMonitor.addModule(&waterSecurity);

    setupLogger(&remote);
//
//    dhtSensor.begin();
//
    // Camera power
    powerManager.drawPower(12345, 20);

    // Arduino power
    powerManager.drawPower(6789, 5);
}

bool isDiving = false;

void loop() {

//    engine.work();
//    sensorMonitor.work();
    remote.work(&isDiving);
    depthController.work();
    ballastController.work();
//    powerManager.work();
//
//    if (isDiving) {
//        securityMonitor.work();
//    }

//    engine.move(255, 127, 100, 255);

}