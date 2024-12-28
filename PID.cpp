#include "PID.h"
#include "config.h"
#include "algorithm.cpp"
#include <chrono>

PID::PID(float p, float i, float d, float max_value)
    : kp(p), ki(i), kd(d),
    max_value(max_value),
    error(0), prev_error(0),
    integral(0), output(0),
    lastTime(std::chrono::system_clock::now()) {
}

float PID::update(float setpoint, float measured_value)
{
    // Get the current time and calculate the time difference (dt) in milliseconds
    auto now = std::chrono::system_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();

    // Enforce minimum update interval (50 ms)
    if (dt < 50) {
        return output; // No update, return the last output
    }

    // Update the last time to the current time
    lastTime = now;

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

    return output * 0.01;
}
