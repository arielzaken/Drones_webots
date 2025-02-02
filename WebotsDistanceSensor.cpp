#include "WebotsDistanceSensor.h"
#include "webotsController.h"

WebotsDistanceSensor::WebotsDistanceSensor(WebotsController& wc, const char* name)
{
	dis = wc.getRobot()->getDistanceSensor(name);
	dis->enable(TIME_STEP);
}

float WebotsDistanceSensor::read()
{
	return (float)(dis->getValue());
}
