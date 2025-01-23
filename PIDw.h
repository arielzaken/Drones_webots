#pragma once


#include "Controller_I.h"
#include <chrono>
#include "Primitives.h"

class PIDw : public Controller_I<float, const Matrix2d&> {
	float kp, ki, kd;
	float error, prev_error, integral;
	float output;
	std::chrono::system_clock::time_point lastTime;
public:
	PIDw(float p, float i, float d);
	float update(const Matrix2d& setpoint, const Matrix2d& measured_value) override;
};