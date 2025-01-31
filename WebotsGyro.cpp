#include "WebotsGyro.h"
#include "webotsController.h"

WebotsGyro::WebotsGyro(WebotsController& wc, const char* name)
{
    gyro = wc.getRobot()->getGyro(name);
    gyro->enable(TIME_STEP);
}

Vector3f WebotsGyro::read()
{
    return MCVector3d(gyro->getValues()).cast<float>();
}
