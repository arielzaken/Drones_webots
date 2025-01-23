#include "VelPID.h"
#include "algorithm.cpp"

VelPID::VelPID(const VelPID_params_t& params) : 
    pidx(params.kp_x, params.ki_x, params.kd_x),
    pidy(params.kp_y, params.ki_y, params.kd_y),
    pidz(params.kp_z, params.ki_z, params.kd_z),
    pidw(params.kp_w, params.ki_w, params.kd_w),
    baseThrottle(params.baseThrottle) 
{}

ControllSignal VelPID::update(Pos to, Pos value)
{
    ControllSignal res;
    res[X] = (uint16_t)clamp(1500 + pidx.update(to[X], value[X]), 1000, 2000);
    res[Y] = (uint16_t)clamp(1500 + pidy.update(to[Y], value[Y]), 1000, 2000);
    res[Z] = (uint16_t)clamp(baseThrottle + pidz.update(to[Z], value[Z]), 1000, 2000);
    res[3] = (uint16_t)clamp(1500 + pidw.update({ to[Wx], to[Wy]}, { value[Wx], value[Wy] }), 1000, 2000);
    return res;
}
