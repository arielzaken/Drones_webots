#define TIME_STEP 32

#define REALL_TIME_STEP (TIME_STEP/1000.0) 

#define SIGN(x) ((x) > 0) - ((x) < 0)
#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))
#define MAP(x, in_min, in_max, out_min, out_max)  ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

#include "DroneController_I.h"
#include "webotsController.h"
#include "Stabilizer.h"
#include "VelPID_Z.h"
#include "HoverBehavior.h"
#include "Vel_B.h"
#include <thread>
#include <chrono>
#include <iostream>

WebotsController wc; 
WebotsAltSensor alt(wc);
WebotsVelocitySensor vel(wc);

VelPID velPIDz({
		100.0, 5.0, 10.0, // X axis PID -> roll
		100.0, 5.0, 10.0, // y axis PID -> yaw
		50.0, 1.0, 30.0, // z axis PID -> throttle
		100.0, 5.0, 10.0, // w turn PID -> pitch
		1179             // baseThrottle
	});
Stabilizer stabelizer(wc, velPIDz, vel);
HoverBehavior hb(alt, 5);
Vel_B vb({ 0,0,0,0.2 });


int main() {
	wc.enable();
	stabelizer.begin();
	uint8_t hb_h = stabelizer.addBehavior(vb);
	wc.wait();
	stabelizer.end();
	return 0;
}