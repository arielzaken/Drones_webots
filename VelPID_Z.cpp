#include "VelPID_Z.h"

#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))

VelPID_Z::VelPID_Z(float kp, float ki, float kd, uint16_t bt) : pid(kp, ki, kd, 1000), baseThrottle(bt){}

Twist<uint16_t> VelPID_Z::update(Velocity to, Velocity value)
{ 
    return { 1500, 1500, (uint16_t)CLAMP(baseThrottle + pid.update(to[Z], value[Z]), 1000, 2000), 1500};
}
