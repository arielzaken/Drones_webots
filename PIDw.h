#pragma once


#include "Controller_I.h"
#include <chrono>
#include "Primitives.h"

class PIDw : public Controller_I<float, const Matrix2f&> {
	float kp, ki, kd;
	float error, prev_error, integral;
	float output;
public:
	PIDw(float p, float i, float d);
	float update(const Matrix2f& setpoint, const Matrix2f& measured_value) override;
};