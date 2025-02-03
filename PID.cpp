#include "PID.h"
#include "config.h"
#include "algorithm.cpp"
#include <chrono>

PID::PID(float p, float i, float d)
    : kp(p), ki(i), kd(d),
    error(0), prev_error(0),
    integral(0), output(0) {
}

float PID::update(float setpoint, float measured_value)
{
    // Get the current time and calculate the time difference (dt) in milliseconds
    getDt;

    // Calculate the error
    error = setpoint - measured_value;

    // Update the integral term with anti-windup
    integral = clamp(integral + (error * dt), -1, 1);

    // Calculate the derivative term, ensure no division by zero
    float derivative = (dt > 0) ? (error - prev_error) / dt : 0;

    // Compute the PID output
    output = (kp * error) + (ki * integral) + (kd * derivative);

    // Update previous error
    prev_error = error;

    return output;
}
