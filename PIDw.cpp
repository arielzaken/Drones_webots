#include "PIDw.h"
#include "config.h"
#include "algorithm.cpp"

PIDw::PIDw(float p, float i, float d)
    : kp(p), ki(i), kd(d),
    error(0), prev_error(0),
    integral(0), output(0),
    lastTime(std::chrono::system_clock::now()) {
}

float PIDw::update(Vector2d setpoint, Vector2d measured_value)
{
    // Get the current time and calculate the time difference (dt) in milliseconds
    auto now = std::chrono::system_clock::now();
#ifdef WEBOTS_STEP_TIME_MS
    auto dt = (float)WEBOTS_STEP_TIME_MS;
#else
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();
    // Enforce minimum update interval (50 ms)
    if (dt < 50) {
        return output; // No update, return the last output
    }
#endif // WEBOTS_STEP_TIME

    // Update the last time to the current time
    lastTime = now;

    // Calculate the error
    if(setpoint[X]*measured_value[Y] > measured_value[X] * setpoint[Y])
        error = std::acos(setpoint.dot(measured_value));
    else
        error = -std::acos(setpoint.dot(measured_value));
    error = 100 * error / ((error - PI) * (error + PI));

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

