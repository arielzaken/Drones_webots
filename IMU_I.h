#pragma once

#include "Sensor_I.h"
#include "Primitives.h"

/*
* an IMU sensor interface in the format ENU angles
*/
class IMU_I : public Sensor_I<Vector3f>{};