#pragma once

#include "Sensor_I.h"
#include "Primitives.h"

// a GPS sensor Interface, format: [x, y, z, v]
// x, y, z - the cordinates
// v - the magnetude velocity, -1 if not implemented; 
class GPS_I : public Sensor_I<Vector4f>{
};