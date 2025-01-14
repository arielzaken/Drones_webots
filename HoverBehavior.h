#pragma once
#include "Behavior_I.h"
#include "AltSensor.h"

class HoverBehavior : public Behavior_I
{
private:
    AltSensor* altSensor;
    uint16_t requiredAlt = 0;
public:
    HoverBehavior(AltSensor& altSensor, uint16_t reqAlt) : altSensor(&altSensor), requiredAlt(reqAlt) {}
    virtual Velocity calcBehavior() override; 
    virtual void setup() override;
};
