#include "VelPID.h"
#include "algorithm.cpp"

VelPID::VelPID(const VelPID_params_t& params) : 
    pidx(params.kp_x, params.ki_x, params.kd_x),
    pidy(params.kp_y, params.ki_y, params.kd_y),
    pidz(params.kp_z, params.ki_z, params.kd_z),
    pidw(params.kp_w, params.ki_w, params.kd_w)
{}

ControllSignal VelPID::update(Frame to, Frame value)
{
    ControllSignal res;
    res[X] = (int16_t)pidx.update(to.pos[X], value.pos[X]);
    res[Y] = (int16_t)pidy.update(to.pos[Y], value.pos[Y]);
    res[Z] = (int16_t)pidz.update(to.pos[Z], value.pos[Z]);
    res[3] = (int16_t)pidw.update(to.ori, value.ori);
    return res;
}
