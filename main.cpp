#include "webotsController.h"
#include "Stabilizer.h"
//#include "SimpleLframeMaker.h"
#include "BehaviorLFrameMaker.h"
#include "HoverBehavior.h"
#include "Vel_B.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "VelPID.h"

WebotsController wc;
WebotsAltSensor alt(wc);
WebotsGlobalOrientaionSensor gos(wc);
 
VelPID controller({
		50, 0, 40, // X axis PID -> roll
		50, 0, 40, // y axis PID -> yaw
		15, 1, 25, // z axis PD -> throttle
		10, 0.1, 10 // w turn PD -> pitch
	});

//Frame lFrame({0,0,5}, 0); pwsh.exe
//
//SimpleLframeMaker sLFM(lFrame);

BehaviorLFrameMaker bLFM;
HoverBehavior hb(alt, 2);
Vel_B vb({ 0,0,0,0.2 });
Vel_B vt({ 1,-1,0,0 });


Stabilizer stabelizer(wc, controller, gos, bLFM);

using namespace std::chrono;

int main() {
	//std::this_thread::sleep_for(seconds(5));
	wc.enable();
	stabelizer.setBaseThrottle(1179);
	stabelizer.begin();
	BehaviorHandle_t hb_h = bLFM.addBehavior(hb);
	std::this_thread::sleep_for(seconds(3));
	//BehaviorHandle_t vb_h = bLFM.addBehavior(vb);
	//std::this_thread::sleep_for(seconds(5));
	//bLFM.removeBehavior(vb_h);
	BehaviorHandle_t vt_h = bLFM.addBehavior(vt);
	std::this_thread::sleep_for(seconds(20));
	bLFM.removeBehavior(vt_h);
	hb.SetRequiredAlt(0.2);


	wc.wait();
	stabelizer.end();
	return 0;
}