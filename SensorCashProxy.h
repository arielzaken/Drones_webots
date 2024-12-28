#pragma once
#include "Sensor_I.h"
#include <stdint.h>
#include "config.h"
#include <thread>

using namespace std;

template <typename T>
class SensorCashProxy : public Sensor_I<T> {
    Sensor_I<T>* m_pSensor;
    T data;
    uint16_t spoilTime;
    thread* pThread = nullptr;
    static void proxyLoop(void* args);

public:
    SensorCashProxy(Sensor_I<T> &m_pSensor, uint16_t spoilTime);
    ~SensorCashProxy();
    T read() override;
};

// Definitions moved from the .cpp file

template <typename T>
struct sensor_loop_args_t {
    Sensor_I<T>* sensor;
    uint16_t spoil;
    T* data;
};

template <typename T>
void SensorCashProxy<T>::proxyLoop(void *_args) {
    sensor_loop_args_t<T>* args = static_cast<sensor_loop_args_t<T>*>(_args);
    Sensor_I<T>* sensor = args->sensor;
    uint16_t spoil = args->spoil;
    T* data = args->data;
    for(;;) {
        *(data) = sensor->read();
        vTaskDelay(spoil / portTICK_PERIOD_MS);
    }
}

template <typename T>
SensorCashProxy<T>::SensorCashProxy(Sensor_I<T> &_m_pSensor, uint16_t _spoilTime)
    : m_pSensor(&_m_pSensor), spoilTime(_spoilTime) {
    // Create task for proxy loop
    sensor_loop_args_t<T>* args = new sensor_loop_args_t<T>{&_m_pSensor, _spoilTime, &data};
    pThread = new thread(proxyLoop, "Proxy Loop", 2048, args, 1, nullptr);
}

template<typename T>
inline SensorCashProxy<T>::~SensorCashProxy()
{
    if (pThread) {
        delete pThread;
    }
}

template <typename T>
T SensorCashProxy<T>::read() {
    return data;
}
