#pragma once
#include "Behavior_I.h"
#include "AltSensor.h"

class HoverBehavior : public Behavior_I
{
private:
    AltSensor* altSensor;
    float requiredAlt = 0.0;
public:
    HoverBehavior(AltSensor& altSensor, float reqAlt) : altSensor(&altSensor), requiredAlt(reqAlt) {}
    void SetRequiredAlt(float reqAlt);
    virtual Velocity calcBehavior() override; 
    virtual void setup() override;
};
