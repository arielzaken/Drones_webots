#pragma once

#include "Controller_I.h"
#include <stdint.h>

class P3I : public Controller_I<float, float>
{
    float acc;
    float kp, ki;
public:
    P3I(float _kp, float _ki) : acc(0.0), kp(_kp), ki(_ki) {}
    virtual float update(float setpoint, float measured_value) override;
};