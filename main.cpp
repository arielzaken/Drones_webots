
#include <thread>
#include <chrono>
#include <iostream>

/* controllers */
#include "VelPID.h"

// DroneController and sensors:
#include "webotsController.h"
#include "WebotsAltSensor.h"
#include "WebotsGPS.h"
#include "WebotsCompass.h"
#include "GPS_COM_LFS.h"

/* stabelizer and Lframe maker *///----------------------------------
#include "Stabilizer.h"
//#include "SimpleLframeMaker.h"
#include "BehaviorLFrameMaker.h"

/* behaviors */
#include "GradualVelocityBehavior.h"
#include "HoverBehavior.h"
#include "Vel_B.h"


WebotsController wc;
WebotsAltSensor alt(wc, "altimeter");
WebotsGPS gps(wc, "gps");
WebotsCompass com(wc, "compass");
GPS_COM_LFS gos(gps, com);

//VelPID controller({
//		50, 1, 40, // X axis PID -> roll
//		50, 1, 40, // y axis PID -> yaw
//		15, 1, 25, // z axis PID -> throttle
//		10, 0.1, 10 // w turn PID -> pitch
//	});
//
////Frame lFrame({0,0,5}, 0); pwsh.exe
////
////SimpleLframeMaker sLFM(lFrame);
//
//BehaviorLFrameMaker bLFM;
//HoverBehavior hb(alt, 1);
//Vel_B vb({ 0,0,0,0.2 });
//Vel_B vt({ 1,-1,0,0 });
//GradualVelocityBehavior gvb({ 5, -5, 0, 0 }, 5);
//
//Stabilizer stabelizer(wc, controller, gos, bLFM);

using namespace std::chrono;

int main() {
	//std::this_thread::sleep_for(seconds(5));
	wc.enable();
	//stabelizer.setBaseThrottle(1179);
	//stabelizer.begin();
	//bLFM.addBehavior(hb);
	//std::this_thread::sleep_for(seconds(3));
	////bLFM.addBehavior(vb);
	////std::this_thread::sleep_for(seconds(5));
	////bLFM.removeBehavior(vb);
	//std::cout << "gvb\n";
	//bLFM.addBehavior(gvb);
	//std::this_thread::sleep_for(seconds(15));
	//bLFM.removeBehavior(gvb);
	//hb.SetRequiredAlt(0.1);
	while (wc.checkIsRunning()) {
		std::cout << gos.read() << std::endl;
		std::this_thread::sleep_for(milliseconds(200));
	}

	wc.wait();
	//stabelizer.end();
	return 0;
}