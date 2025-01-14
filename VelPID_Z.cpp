#include "VelPID_Z.h"

#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))

VelPID::VelPID(const VelPID_params_t& params) : 
    pidx(params.kp_x, params.ki_x, params.kd_x, 1000),
    pidy(params.kp_y, params.ki_y, params.kd_y, 1000),
    pidz(params.kp_z, params.ki_z, params.kd_z, 1000),
    pidw(params.kp_w, params.ki_w, params.kd_w, 1000),
    baseThrottle(params.baseThrottle)
{

}

Twist<uint16_t> VelPID::update(Velocity to, Velocity value)
{ 
    return { 
        (uint16_t)CLAMP(1500 + pidx.update(to[X], value[X]), 1000, 2000),
        (uint16_t)CLAMP(1500 + pidy.update(to[Y], value[Y]), 1000, 2000),
        (uint16_t)CLAMP(baseThrottle + pidz.update(to[Z], value[Z]), 1000, 2000),
        (uint16_t)CLAMP(1500 + pidw.update(to[W], value[W]), 1000, 2000)
    };
}
