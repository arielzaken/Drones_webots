#pragma once
#include "DistanceSensor.h"
#include <functional>

template <typename T>
class SensorMock : public Sensor_I<T> {
    std::function<T()> hook; // Callable with no parameters returning T
public:
    /// @brief Constructor that accepts a callable to simulate sensor behavior.
    /// @param _hook Function or lambda that returns T
    explicit SensorMock(const std::function<T()>& _hook) : hook(_hook) {}

    /// @brief Allows updating the mock behavior dynamically.
    /// @param newHook A new callable to replace the current one
    void setHook(const std::function<T()>& newHook) {
        hook = newHook;
    }

    /// @brief Reads the sensor value.
    /// @return The result of the hooked function, or default value if the hook is invalid.
    virtual T read() override {
        if (hook) {
            return hook();
        }
        return T(); // Return default value for type T
    }
};
