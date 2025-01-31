#include "WebotsIMU.h"
#include "webotsController.h"

WebotsIMU::WebotsIMU(WebotsController& wc, const char* name)
{
	imu = wc.getRobot()->getInertialUnit(name);
	imu->enable(TIME_STEP);
}

Vector3f WebotsIMU::read()
{
	return MCVector3d(imu->getRollPitchYaw()).cast<float>();
}
