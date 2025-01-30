#pragma once
#include <webots/GPS.hpp>
#include "GPS_I.h"

class WebotsController;

class WebotsGPS : public GPS_I {
	webots::GPS* gps;
public:
	WebotsGPS(WebotsController& _wc, const char* name);
	// Inherited via AltSensor
	Vector4f read() override;
};