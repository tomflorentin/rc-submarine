//
// Created by tomfl on 5/9/2023.
//

#ifndef SURFACE_STATUS_HPP
#define SURFACE_STATUS_HPP


#include <mutex>

class Status {
public:
    void setLightStatus(uint8_t intensity);
    uint8_t getLightStatus();

    void setTemperature(float temperature);
    float getTemperature();

    void setHumidity(float humidity);
    float getHumidity();

    void setDepth(float depth);
    float getDepth();

    void setPower(uint8_t power);
    uint8_t getPower();

    void setBallastFill(uint8_t ballastFill);
    uint8_t getBallastFill();

    void setAlert(uint8_t alert);
    uint8_t getAlert();

    void setCameraAngle(uint8_t angle);
    uint8_t getCameraAngle();

    void setInsidePressure(float pressure);
    float getInsidePressure();

    void setBatteryLevel(uint8_t level);
    uint8_t getBatteryLevel();

    void setIsDiving(bool _diving);
    bool getIsDiving();

    std::string getStatusText();

private:
    uint8_t lightStatus = 0;
    float temperature = 0;
    float humidity = 0;
    float depth = 0;
    uint8_t power = 0;
    uint8_t ballastFill = 0;
    uint8_t alert = 0;
    uint8_t cameraAngle = 0;
    float insidePressure = 0;
    uint8_t batteryLevel = 0;
    bool isDiving = false;

    std::mutex lck;
};


#endif //SURFACE_STATUS_HPP
