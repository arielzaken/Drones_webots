#include "webotsController.h"
#include "Stabilizer.h"
//#include "SimpleLframeMaker.h"
#include "BehaviorLFrameMaker.h"
#include "GradualVelocityBehavior.h"
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
		50, 1, 40, // X axis PID -> roll
		50, 1, 40, // y axis PID -> yaw
		15, 1, 25, // z axis PID -> throttle
		10, 0.1, 10 // w turn PID -> pitch
	});

//Frame lFrame({0,0,5}, 0); pwsh.exe
//
//SimpleLframeMaker sLFM(lFrame);

BehaviorLFrameMaker bLFM;
HoverBehavior hb(alt, 1);
Vel_B vb({ 0,0,0,0.2 });
Vel_B vt({ 1,-1,0,0 });
GradualVelocityBehavior gvb({ 5, -5, 0, 0 }, 15);

Stabilizer stabelizer(wc, controller, gos, bLFM);

using namespace std::chrono;

int main() {
	std::this_thread::sleep_for(seconds(5));
	wc.enable();
	stabelizer.setBaseThrottle(1179);
	stabelizer.begin();
	bLFM.addBehavior(hb);
	std::this_thread::sleep_for(seconds(3));
	//bLFM.addBehavior(vb);
	//std::this_thread::sleep_for(seconds(5));
	//bLFM.removeBehavior(vb);
	std::cout << "gvb\n";
	bLFM.addBehavior(gvb);
	std::this_thread::sleep_for(seconds(15));
	bLFM.removeBehavior(gvb);
	hb.SetRequiredAlt(0.1);


	wc.wait();
	stabelizer.end();
	return 0;
}