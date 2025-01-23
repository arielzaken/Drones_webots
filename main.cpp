#include "webotsController.h"
#include "Stabilizer.h"
#include "SimpleLframeMaker.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "VelPID.h"

WebotsController wc;
WebotsAltSensor alt(wc);
WebotsGlobalOrientaionSensor gos(wc);
 
VelPID controller({
		0, 0, 0, // X axis PID -> roll
		0, 0, 0, // y axis PID -> yaw
		2, 0, 30, // z axis PD -> throttle
		2, 0, 15, // w turn PD -> pitch
		1179             // baseThrottle
	});

SimpleLframeMaker sLFM(Pos{0, 0, 5, -1, 0});
Stabilizer stabelizer(wc, controller, gos, sLFM);
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