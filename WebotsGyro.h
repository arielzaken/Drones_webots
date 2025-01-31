#pragma once
#include "Gyro_I.h"
#include <webots/gyro.hpp>

class WebotsController;

class WebotsGyro : public Gyro_I {
	webots::Gyro* gyro;
public:
	WebotsGyro(WebotsController& wc, const char* name);

	// Inherited via Gyro_I
	Vector3f read() override;

};