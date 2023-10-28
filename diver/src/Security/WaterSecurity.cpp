//
// Created by tomfl on 3/24/2023.
//

#include "WaterSecurity.hpp"
#include "RemoteControl/protocol.hpp"

WaterSecurity::WaterSecurity(uint8_t pinFront, uint8_t pinBack, uint8_t pinSeringueGasket, uint8_t pinSeringueOut) :
    front(pinFront),
    back(pinBack),
    seringueGasket(pinSeringueGasket),
    seringueOut(pinSeringueOut)
    {

}

void WaterSecurity::setup() {
    this->front.setup();
    this->back.setup();
    this->seringueOut.setup();
    this->seringueGasket.setup();
}

Alert WaterSecurity::checkSecurity() {
    Alert water = Alert::None;

    if (this->front.readRaw() > 100)
        water = static_cast<Alert>(water | Alert::WaterFront);
    if (this->back.readRaw() > 100)
        water = static_cast<Alert>(water | Alert::WaterBack);
    if (this->seringueGasket.readRaw() > 100)
        water = static_cast<Alert>(water | Alert::WaterSeringueGasket);
    if (this->seringueOut.readRaw() > 100)
        water = static_cast<Alert>(water | Alert::WaterSeringueOut);
    return water;
}
