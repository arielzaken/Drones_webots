//#define TIME_STEP 32
//
//#define REALL_TIME_STEP (TIME_STEP/1000.0) 
//
//#define SIGN(x) ((x) > 0) - ((x) < 0)
//#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))
//#define MAP(x, in_min, in_max, out_min, out_max)  ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
//
//#include "DroneController_I.h"
//#include "webotsController.h"
//#include "Stabilizer.h"
//#include "VelPID_Z.h"
//#include "HoverBehavior.h"
//#include "Vel_B.h"
//#include <thread>
//#include <chrono>
//#include <iostream>

//WebotsController wc; 
//WebotsAltSensor alt(wc);
//WebotsVelocitySensor vel(wc);
//
//VelPID velPIDz({
//		10.0, 1.0, 20.0, // X axis PID -> roll
//		10.0, 1.0, 20.0, // y axis PID -> yaw
//		1.0, 1.0, 0.0, // z axis PID -> throttle
//		10.0, 1.0, 20.0, // w turn PID -> pitch
//		1179             // baseThrottle
//	});
//Stabilizer stabelizer(wc, velPIDz, vel);
//HoverBehavior hb(alt, 2);
//Vel_B twist_B({ 0,0,0,0.2 });
//Vel_B translate_B({ -1,1,0,0 });
//Vel_B translate2_B({ 0,0,1,0 });

#include <iostream>
#include "Primitives.h"
using namespace std;
int main() {
    Vec3D<double> Ivel{ 1, 2, 3 };
    Matrix3d Mframe = Eigen::AngleAxisd(1.2, Eigen::Vector3d::UnitZ()).matrix();
    cout << "Mframe before rot:\n" << Mframe << endl;
    Mframe = Eigen::AngleAxisd(0.4, Eigen::Vector3d(-0.8, -0.6, 0)) * Mframe;
    cout << "Mframe after rot:\n" << Mframe << endl;
    // find the rot axis of the translate 
    Vec3D<double> rotAxis = Eigen::Vector3d::UnitZ().cross(Mframe.row(Z)).normalized();
    cout << "rot axis:\n" << rotAxis << endl;

    double angle_rad = std::acos(Mframe(2, 2)); // get the angle to rotate back to aline with the Iframe
    cout << "rot angle:\n" << angle_rad << endl;

    Matrix3d Lframe = Eigen::AngleAxisd(-angle_rad, rotAxis) * Mframe;
    cout << "Lframe:\n" << Lframe << endl;

    //std::cout << Lframe << std::endl;
    Vec3D<double> Lvel = Lframe.transpose() * Ivel;
	return 0;
}