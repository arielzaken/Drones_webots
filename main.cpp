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

VelPID_Z velPIDz(3.0, 1.0, 30.0, 1179);
Stabilizer stabelizer(wc, velPIDz, vel);
HoverBehavior hb(alt, 5);
Vel_B vb({ 0,0,2,0 });


int main() {
	std::this_thread::sleep_for(std::chrono::seconds(5));
	wc.enable();
	stabelizer.begin();
	uint8_t hb_h = stabelizer.addBehavior(vb);
	//double lastRead = -1;
	//uint16_t baseThrottle = 1178;
	////for (;;) {
	////    const double value = alt.read();
	////	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	////    std::cout << "Sensor value is: " << value << endl;
	////    if (lastRead != -1 && value >= 0.1)
	////        break;
	////    lastRead = value;
	////    baseThrottle += 1;
	////	wc.setThrottle(baseThrottle);
	////};
	////wc.setThrottle(baseThrottle);

	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//wc.setYaw(1750);
	//wc.setRoll(1750);
	//double lastI = 0;
	//double lastError = 0;
	//double kp;
	//double ki;
	//double kd;
	//
	//double from = 0;
	//double to = 5;
	//int counter = 0;
	//while(wc.isRunning()) {
	//    const double value = alt.read();
	//    double error = to - value;
	//    if (abs(error) < abs(to - from) / 5)
	//    {
	//        //std::cout << " 1 | ";
	//        kp = 3;
	//        ki = 1;
	//        kd = 30;
	//    }
	//    else if (abs(error) < 2 * abs(to - from) / 3)
	//    {
	//        //std::cout << " 2 | ";
	//        kp = 5;
	//        ki = 5;
	//        kd = 15;
	//    }
	//    else
	//    {
	//        //std::cout << " 3 | ";
	//        kp = 15;
	//        ki = 10;
	//        kd = 0;
	//    }
	//    double P = error;
	//    double D = (error - lastError) / REALL_TIME_STEP;
	//    double I = lastI;
	//    lastI = CLAMP(lastI + error * REALL_TIME_STEP, -1, 1);
	//    lastError = error;
	//
	//    uint16_t throttle = CLAMP(baseThrottle + (P * kp + I * ki + D * kd), 1000, 2000); 
	//    //std::cout << value << " | " << P << " " << I << " " << D << " | " << throttle << std::endl;

	//	Velocity temp = vel.read();
	//	printf("(%f, %f, %f, %f)\n", temp[0], temp[1], temp[2], temp[3]);

	//	wc.setThrottle(throttle);
	//};


	//std::cout << "base is: " << baseThrottle << std::endl;

	wc.wait();
	stabelizer.end();
	return 0;
}