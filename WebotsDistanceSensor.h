#pragma once

#include "DistanceSensor_I.h"
#include <webots/DistanceSensor.hpp>

class WebotsController;

class WebotsDistanceSensor : public DistanceSensor_I{
	webots::DistanceSensor* dis;
public:

	WebotsDistanceSensor(WebotsController& wc, const char* name);

	float read() override;
};