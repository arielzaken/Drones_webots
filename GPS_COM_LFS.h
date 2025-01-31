#pragma once
#include "Primitives.h"
#include "LFS_I.h"
#include "GPS_I.h"
#include "IMU_I.h"

/*
* GPS and a Compass based LFrame Sensor
*/
class GPS_IMU_LFS : public LFS_I {
	GPS_I* gps;
	IMU_I* imu;
public:
	GPS_IMU_LFS(GPS_I& gps, IMU_I& imu);
	// Inherited via AltSensor
	Frame read() override;
};