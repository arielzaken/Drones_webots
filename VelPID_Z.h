#pragma once

#include "Controller_I.h"
#include "Primitives.h"
#include "PID.h"

class VelPID_Z : public Controller_I<Twist<uint16_t>, Velocity>
{
	PID pid;
	uint16_t baseThrottle;
public:
	VelPID_Z(float kp, float ki, float kd, uint16_t baseThrottle);
	// Inherited via Controller_I
	virtual Twist<uint16_t> update(Velocity setpoint, Velocity measured_value) override;
};

