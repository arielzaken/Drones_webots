#pragma once

#include "Controller_I.h"
#include "Primitives.h"
#include "P3I.h"
#include <stdint.h>

class VelP3I : public Controller_I<Twist<uint16_t>, Velocity>
{
    P3I xP3I, yP3I, zP3I, wP3I;
public:
    VelP3I(float _kp, float _ki) :  xP3I(_kp, _ki), yP3I(_kp, _ki), zP3I(_kp, _ki), wP3I(_kp, _ki) {}
    virtual Twist<uint16_t> update(Velocity setpoint, Velocity measured_value) override;
};