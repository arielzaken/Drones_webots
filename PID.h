#pragma once
#include "Controller_I.h"
#include <cstdint>
#include <chrono>

class PID : public Controller_I<float, float> {
	float kp, ki, kd;
	float error, prev_error, integral;
	float output;
	int32_t max_value;
	std::chrono::system_clock::time_point lastTime;
public:
	PID(float p, float i, float d, int32_t max_value);
	virtual float update(float setpoint, float measured_value) override;
};