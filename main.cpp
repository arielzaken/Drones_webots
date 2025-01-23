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
		10, 0, 25, // X axis PID -> roll
		10, 0, 25, // y axis PID -> yaw
		15, 0, 25, // z axis PD -> throttle
		4, 0, 10 // w turn PD -> pitch
	});

Frame lFrame({0,0,5}, 0);

SimpleLframeMaker sLFM(lFrame);
Stabilizer stabelizer(wc, controller, gos, sLFM);
//HoverBehavior hb(alt, 5);
//Vel_B vb({ 0,0,0,0.2 });

using namespace std::chrono;

int main() {
	wc.enable();
	stabelizer.setBaseThrottle(1179);
	stabelizer.begin();

	//std::this_thread::sleep_for(seconds(5));
	//lFrame.setOri(PI/2);
	//sLFM.setLframe(lFrame);
	std::this_thread::sleep_for(seconds(5));
	lFrame.pos = { 5,5,5 };
	sLFM.setLframe(lFrame);
	std::this_thread::sleep_for(seconds(10));
	lFrame.pos = { -5,-5,2 };
	sLFM.setLframe(lFrame);
	//uint8_t vb_h = stabelizer.addBehavior(vb);

	wc.wait();
	stabelizer.end();
	return 0;
}