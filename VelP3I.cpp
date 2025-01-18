#include "VelP3I.h"
#include "algorithm.cpp"

using namespace std;

ControllSignal VelP3I::update(Velocity setpoint, Velocity measured_value)
{
    return {
        (uint16_t)clamp(xP3I.update(setpoint[X], measured_value[X]), 1000, 2000),
        (uint16_t)clamp(yP3I.update(setpoint[Y], measured_value[Y]), 1000, 2000),
        (uint16_t)clamp(zP3I.update(setpoint[Z], measured_value[Z]), 1000, 2000),
        (uint16_t)clamp(wP3I.update(setpoint[W], measured_value[W]), 1000, 2000),
    };
}