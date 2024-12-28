#pragma once
#include "stdint.h"
class DroneController_I{
public:
    virtual void setThrottle(uint16_t throttle) = 0;
    virtual void setPitch(uint16_t pitch) = 0;
    virtual void setYaw(uint16_t yaw) = 0;
    virtual void setRoll(uint16_t roll) = 0;
    virtual void setAUX(uint16_t channle, uint16_t auxValue) = 0;

    virtual void arm() = 0;
    virtual void disarm() = 0;
    virtual void disable() = 0;
    virtual void enable() = 0;
};