
#include <thread>
#include <chrono>
#include <iostream>

/* controllers */
#include "VelPID.h"

// DroneController and sensors:
#include "webotsController.h"
#include "WebotsAltSensor.h"
#include "WebotsGPS.h"
#include "WebotsIMU.h"
#include "WebotsDistanceSensor.h"
#include "GPS_COM_LFS.h"

/* stabelizer and Lframe maker *///----------------------------------
#include "Stabilizer.h"
//#include "SimpleLframeMaker.h"
#include "BehaviorLFrameMaker.h"

/* behaviors */
#include "GradualVelocityBehavior.h"
#include "HoverBehavior.h"
#include "Vel_B.h"
#include "ObsticalAvoidanseBehavior.h"


WebotsController wc;
WebotsAltSensor alt(wc, "altimeter");
WebotsGPS gps(wc, "gps");
WebotsIMU imu(wc, "inertial unit");

DistanceSensor_I* disR[] = {
	new WebotsDistanceSensor(wc, "disR1"),
	new WebotsDistanceSensor(wc, "disR2"),
	new WebotsDistanceSensor(wc, "disR3"),
	new WebotsDistanceSensor(wc, "disR4"),
	new WebotsDistanceSensor(wc, "disR5"),
	new WebotsDistanceSensor(wc, "disR6"),
	new WebotsDistanceSensor(wc, "disR7"),
	new WebotsDistanceSensor(wc, "disR8")
};

GPS_IMU_LFS gos(gps, imu);

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
HoverBehavior hb(alt, 5);
Vel_B vb({ 0,0,0,0.2 });
Vel_B vt({ 1,-1,0,0 });
ObsticalAvoidanseBehavior oab(disR);
GradualVelocityBehavior gvb({ 5, -5, 0, 0 }, 5);

Stabilizer stabelizer(wc, controller, gos, bLFM);

using namespace std::chrono;

int main() {
	wc.enable();
	stabelizer.setBaseThrottle(1179);
	stabelizer.begin();
	bLFM.addBehavior(hb);
	bLFM.addBehavior(oab);
	std::this_thread::sleep_for(seconds(3));
	//bLFM.addBehavior(vb);
	//std::this_thread::sleep_for(seconds(5));
	//bLFM.removeBehavior(vb);
	bLFM.addBehavior(gvb);
	std::this_thread::sleep_for(seconds(5));
	bLFM.removeBehavior(gvb);

	wc.wait();
	stabelizer.end();

	for (int i = 0; i < 8; i++) {
		delete disR[i];
	}
	return 0;
}