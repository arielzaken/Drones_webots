#include "PIDw.h"
#include "config.h"
#include "algorithm.cpp"

PIDw::PIDw(float p, float i, float d)
    : kp(p), ki(i), kd(d),
    error(0), prev_error(0),
    integral(0), output(0){
}

float PIDw::update(const Matrix2f& setpoint, const Matrix2f& measured_value)
{
    // Get the current time and calculate the time difference (dt) in float seconds
    getDt;

    Vector2f a = setpoint.col(0);
    Vector2f b = measured_value.col(0);
    float ras = clamp(a.dot(b), -1.0f, 1.0f);
    // Calculate the error
    if(a[X] * b[Y] >= b[X] * a[Y])
        error = std::acos(ras);
    else
        error = -std::acos(ras);
    error = PI2 * error / ((error - PI) * (error + PI));

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

