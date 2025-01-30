#pragma once
#include "Primitives.h"
#include "LFS_I.h"
#include "GPS_I.h"
#include "Compass_I.h"

/*
* GPS and a Compass based LFrame Sensor
*/
class GPS_COM_LFS : public LFS_I {
	GPS_I* gps;
	Compass_I* com;
public:
	GPS_COM_LFS(GPS_I& gps, Compass_I& com);
	// Inherited via AltSensor
	Frame read() override;
};