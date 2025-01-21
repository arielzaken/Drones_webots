#include "DroneController_I.h"
#include "webotsController.h"
#include "Stabilizer.h"
#include "VelPID.h"
#include "HoverBehavior.h"
#include "Vel_B.h"

#include "SimpleLframeMaker.h"
#include <thread>
#include <chrono>
#include <iostream>

WebotsController wc;
WebotsAltSensor alt(wc);
WebotsGlobalOrientaionSensor gos(wc);

VelPID velPIDz({
		0, 0, 0, // X axis PID -> roll
		0, 0, 0, // y axis PID -> yaw
		50, 0.001, 200000, // z axis PID -> throttle
		0, 0, 0, // w turn PID -> pitch
		1179             // baseThrottle
	});

SimpleLframeMaker sLFM({0, 0, 5, 0});
Stabilizer stabelizer(wc, velPIDz, gos, sLFM);
//HoverBehavior hb(alt, 5);
//Vel_B vb({ 0,0,0,0.2 });


int main() {
	wc.enable();
	stabelizer.begin();

	//uint8_t vb_h = stabelizer.addBehavior(vb);
	wc.wait();
	stabelizer.end();
	return 0;
}