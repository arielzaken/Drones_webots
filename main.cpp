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
		10, 1.0, 10.0, // w turn PID -> pitch
		1175             // baseThrottle
	});
Stabilizer stabelizer(wc, velPIDz, vel);
HoverBehavior hb(alt, 5);
Vel_B vb({ 0,0,0,0.2 });


int main() {
	wc.enable();
	stabelizer.begin();
	uint8_t hb_h = stabelizer.addBehavior(hb);
	//uint8_t vb_h = stabelizer.addBehavior(vb);
	wc.wait();
	stabelizer.end();
	return 0;
}