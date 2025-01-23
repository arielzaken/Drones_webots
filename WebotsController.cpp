#include "webotsController.h"
#include <webots/DistanceSensor.hpp>
#include <webots/Altimeter.hpp>
#include <webots/Motor.hpp>
#include <webots/Gyro.hpp>
#include "algorithm.cpp"

using namespace webots;

constexpr auto Kp = 0.05;
constexpr auto Kd = 0.01;

#define REALL_TIME_STEP (TIME_STEP/1000.0) 
# define PI           3.14159265358979323846  /* pi */

void WebotsController::loop()
{
    double targetPitch, targetRoll, targetYaw, targetThrottle;
    double prevErrorPitch = 0, prevErrorRoll = 0, prevErrorYaw = 0;
    double angx = 0, angy = 0, angz = 0;
    const double maxVel = luMotor->getMaxVelocity();
    while (robot->step(TIME_STEP) != -1) {

        // Normalize inputs to the range [-1, 1] for target control
        targetYaw = -((yaw - 1500.0) / 500.0) * (PI / 4);      // Scale from [1000, 2000] to [-1, 1]
        targetRoll = ((roll - 1500.0) / 500.0) * (PI / 4);    // Scale from [1000, 2000] to [-1, 1]
        targetPitch = ((pitch - 1500.0) / 500.0) * 0.01;  // Scale from [1000, 2000] to [-1, 1]
        targetThrottle = (throttle - 1000.0) / 1000.0;  // Scale from [1000, 2000] to [0, 1]

        // Get the current rotational velocities (gyro values in rad/s)
        const double* val = gyro->getValues();
        double rVelx = val[0]; // Pitch rate (rad/s) 
        double rVely = val[1]; // Roll rate (rad/s) 
        double rVelz = val[2]; // Yaw rate (rad/s)
        angx += rVelx * REALL_TIME_STEP;
        angy += rVely * REALL_TIME_STEP;
        // Calculate errors between target and current gyro values
        double errorYaw = targetYaw - angx;
        double errorRoll = targetRoll - angy;

        // Derivative terms to account for rate of change of error
        double dErrorYaw = (errorYaw - prevErrorYaw) / REALL_TIME_STEP;
        double dErrorRoll = (errorRoll - prevErrorRoll) / REALL_TIME_STEP;

        // PD control calculations for pitch, roll, and yaw
        double correctionYaw = Kp * errorYaw + Kd * dErrorYaw;
        double correctionRoll = Kp * errorRoll + Kd * dErrorRoll;

        // Motor mixing to adjust motor velocities based on corrections
        double luv = clamp(targetThrottle - targetPitch + correctionRoll + correctionYaw, -1, 1) * maxVel;
        double ruv = clamp(targetThrottle + targetPitch - correctionRoll + correctionYaw, -1, 1) * maxVel;
        double ldv = clamp(targetThrottle + targetPitch + correctionRoll - correctionYaw, -1, 1) * maxVel;
        double rdv = clamp(targetThrottle - targetPitch - correctionRoll - correctionYaw, -1, 1) * maxVel;

        // Set motor velocities (in the range [0, max motor speed], adjust signs if needed)
        ruMotor->setVelocity(-ruv);  // Right upper motor
        luMotor->setVelocity(luv);   // Left upper motor
        rdMotor->setVelocity(rdv);   // Right down motor
        ldMotor->setVelocity(-ldv);  // Left down motor

        // Store previous errors for derivative calculation in next loop
        prevErrorRoll = errorRoll;
        prevErrorYaw = errorYaw;
    }

}

WebotsController::WebotsController()
{
    robot = new Supervisor();
    alt = robot->getAltimeter("altimeter");
    alt->enable(TIME_STEP);
    gyro = robot->getGyro("gyro");
    gyro->enable(TIME_STEP);

    ruMotor = robot->getMotor("RUmotor");
    rdMotor = robot->getMotor("RDmotor");
    luMotor = robot->getMotor("LUmotor");
    ldMotor = robot->getMotor("LDmotor");

    ruMotor->setPosition(INFINITY);
    luMotor->setPosition(INFINITY);
    rdMotor->setPosition(INFINITY);
    ldMotor->setPosition(INFINITY);
    ruMotor->setVelocity(0);
    luMotor->setVelocity(0);
    rdMotor->setVelocity(0);
    ldMotor->setVelocity(0);
}

WebotsController::~WebotsController()
{
    delete pThread;
    pThread = nullptr;
    delete robot;
    robot = nullptr;
}

void WebotsController::setThrottle(uint16_t _throttle)
{
    throttle = clamp(_throttle, 1000, 2000);
}

void WebotsController::setPitch(uint16_t _pitch)
{
    pitch = clamp(_pitch, 1000, 2000); 
}

void WebotsController::setYaw(uint16_t _yaw)
{
    yaw = clamp(_yaw, 1000, 2000); 
}

void WebotsController::setRoll(uint16_t _roll)
{
    roll = clamp(_roll, 1000, 2000); 
}

void WebotsController::setAUX(uint16_t channle, uint16_t auxValue)
{
    std::cout << "WebotsController::setAUX not implemented\n";
}

void WebotsController::arm()
{
    std::cout << "WebotsController::arm not implemented\n";
}

void WebotsController::disarm()
{
    std::cout << "WebotsController::disarm not implemented\n";
}

void WebotsController::disable()
{
    if (pThread) {
        delete pThread;
        pThread = nullptr;
    }
}

void WebotsController::enable()
{
    if (!pThread) {
        pThread = new std::thread(&WebotsController::loop, this);
    }
}

void WebotsController::wait()
{
    pThread->join();
}

float WebotsAltSensor::read()
{
    return (float)wc->alt->getValue();
}

//Velocity WebotsVelocitySensor::read()
//{
//    Node* robotNode = wc->robot->getSelf();
//    const double* vel = robotNode->getVelocity();
//    return { (float)vel[0], (float)vel[1], (float)vel[2], (float)vel[5] };
//}

Frame WebotsGlobalOrientaionSensor::read()
{
    Node* robot = wc->robot->getSelf();
    MCVector3d pos(robot->getPosition());
    MCMatrix3d ori(robot->getOrientation());
    double x = ori(1), y = ori(4);
    double len = std::sqrt(x * x + y * y);
    x = (x / len);
    y = (y / len);
    Matrix2d R;
    R << y, -x, x, y;
    return Frame( pos, R );
}
