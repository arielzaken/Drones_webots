#pragma once

#include "Controller_I.h"
#include "Primitives.h"
#include "PID.h"
#include "PIDw.h"

typedef struct VelPID_params_t {
	float kp_x, ki_x, kd_x;
	float kp_y, ki_y, kd_y;
	float kp_z, ki_z, kd_z;
	float kp_w, ki_w, kd_w;
} VelPID_params_t;


class VelPID : public Controller_I<ControllSignal, Frame>
{
	PID pidx, pidy, pidz;
	PIDw pidw;
public:
	VelPID(const VelPID_params_t& params);
	// Inherited via Controller_I
	virtual ControllSignal update(Frame setpoint, Frame measured_value) override;
};

