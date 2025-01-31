#pragma once

#include "IMU_I.h"
#include <webots/InertialUnit.hpp>

class WebotsController;

class WebotsIMU : public IMU_I {
	webots::InertialUnit* imu;
public:
	WebotsIMU(WebotsController& wc, const char* name);
	Vector3f read() override;
};