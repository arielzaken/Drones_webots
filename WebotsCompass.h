#pragma once

#include "Compass_I.h"
#include <webots/Compass.hpp>

class WebotsController;

class WebotsCompass : public Compass_I {
	webots::Compass* com;
public:
	WebotsCompass(WebotsController& wc, const char* name);

	// Inherited via Compass
	Vector3f read() override;
};