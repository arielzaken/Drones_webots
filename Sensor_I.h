#pragma once

template <typename T>
class Sensor_I{
public:
    virtual T read() = 0;
};