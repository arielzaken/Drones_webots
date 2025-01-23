#pragma once


#include "Controller_I.h"
#include <chrono>
#include "Primitives.h"

class PIDw : public Controller_I<float, Vector2d> {
	float kp, ki, kd;
	float error, prev_error, integral;
	float output;
	std::chrono::system_clock::time_point lastTime;
public:
	PIDw(float p, float i, float d);
	float update(Vector2d setpoint, Vector2d measured_value) override;
};