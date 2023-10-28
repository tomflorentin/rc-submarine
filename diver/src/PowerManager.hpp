//
// Created by tomfl on 5/16/2023.
//

#ifndef EMBARQUE_POWERMANAGER_HPP
#define EMBARQUE_POWERMANAGER_HPP

#define MAX_DEVICES 128

class PowerManager {
public:
    PowerManager();

    static PowerManager *instance;

    unsigned short getTotalPowerDrawn() const;
    unsigned short getInstantPower() const;

    void work();
    void drawPower(int id, float watts);

private:
    void registerDevice(int id, unsigned short index, float watts, unsigned long now);
    int findDevice(int id);
    void calcPower(unsigned short index, unsigned long now);

    float totalPowerDrawn = 0;

    int devicesIds[MAX_DEVICES] = {0};
    unsigned long devicesLastCalc[MAX_DEVICES] = {0};
    float devicesCurrentDraw[MAX_DEVICES] = {0};

    unsigned short currentIndex = 0;

};


#endif //EMBARQUE_POWERMANAGER_HPP
