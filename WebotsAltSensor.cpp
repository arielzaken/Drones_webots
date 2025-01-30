#include "WebotsAltSensor.h"
#include "webotsController.h"

WebotsAltSensor::WebotsAltSensor(WebotsController& _wc, const char* name)
{
    alt = _wc.getRobot()->getAltimeter(name);
    alt->enable(TIME_STEP);
}

float WebotsAltSensor::read()
{
    return (float)alt->getValue();
}
