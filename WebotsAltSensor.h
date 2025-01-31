#pragma once

#include "AltSensor.h"
#include <webots/altimeter.hpp>

class WebotsController;

class WebotsAltSensor : public AltSensor_I {
	webots::Altimeter* alt;
public:
	WebotsAltSensor(WebotsController& _wc, const char* name);
	// Inherited via AltSensor
	float read() override;
};