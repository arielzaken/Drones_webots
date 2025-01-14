#pragma once
#include "Behavior_I.h"
#include "Primitives.h"

class Vel_B : public Behavior_I
{
    Velocity vel;
public:
    Vel_B(Velocity target) : vel(target) {}
    void setVel(Velocity _vel) { vel = _vel; }
    virtual Velocity calcBehavior() override; 
    virtual void setup() override;
};