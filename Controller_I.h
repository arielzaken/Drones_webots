#pragma once

template <typename O, typename I>
class Controller_I
{
public:
    virtual O update(I setpoint, I measured_value) = 0;
};
