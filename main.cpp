#include <webots/Robot.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Altimeter.hpp>
#include <webots/Motor.hpp>
#include <iostream>
#include <Windows.h>

using namespace webots;
using namespace std;

#define TIME_STEP 32

#define REALL_TIME_STEP (TIME_STEP/1000.0) 

#define SIGN(x) ((x) > 0) - ((x) < 0)
#define CLAMP(value, low, high) ((value) < (low) ? (low) : ((value) > (high) ? (high) : (value)))
#define MAP(x, in_min, in_max, out_min, out_max)  ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

double baseThrottle = 1.79;

int main(int argc, char** argv) {
    Robot* robot = new Robot();
    double throttle = 0;
    Altimeter* dis = robot->getAltimeter("altimeter");
    dis->enable(TIME_STEP);

    Motor* ruMotor = robot->getMotor("RUmotor");
    Motor* rdMotor = robot->getMotor("RDmotor");
    Motor* luMotor = robot->getMotor("LUmotor");
    Motor* ldMotor = robot->getMotor("LDmotor");

    ruMotor->setPosition(INFINITY);
    luMotor->setPosition(INFINITY);
    rdMotor->setPosition(INFINITY);
    ldMotor->setPosition(INFINITY);
    ruMotor->setVelocity(0);
    luMotor->setVelocity(0);
    rdMotor->setVelocity(0);
    ldMotor->setVelocity(0);

    double lastRead = -1;

    /*while (robot->step(TIME_STEP) != -1) {
        const double value = dis->getValue();
        Sleep(5);
        cout << "Sensor value is: " << value << endl;
        if (lastRead != -1 && value >= 0.1)
            break;
        lastRead = value;
        baseThrottle += 0.01;

        ruMotor->setVelocity(-baseThrottle);
        luMotor->setVelocity(baseThrottle);
        rdMotor->setVelocity(baseThrottle);
        ldMotor->setVelocity(-baseThrottle);
    };*/
    cout << "Base throttle is: " << baseThrottle << endl;
    // Main loop
    double lastI = 0;
    double lastError = 0;
    double kp;
    double ki;
    double kd;

    double from = 0;
    double to = 5;
    int counter = 0;
    while (robot->step(TIME_STEP) != -1) {
        const double value = dis->getValue();
        double error = to - value;
        if (abs(error) < abs(to - from) / 5)
        {
            cout << " 1 | ";
            kp = 3;
            ki = 1;
            kd = 30;
        }
        else if (abs(error) < 2 * abs(to - from) / 3)
        {
            cout << " 2 | ";
            kp = 5;
            ki = 5;
            kd = 10;
        }
        else
        {
            cout << " 3 | ";
            kp = 5;
            ki = 10;
            kd = 0;
        }
        double P = error;
        double D = (error - lastError) / REALL_TIME_STEP;
        double I = lastI;
        lastI = CLAMP(lastI + error * REALL_TIME_STEP, -1, 1);
        lastError = error;

        throttle = baseThrottle + (P * kp + I * ki + D * kd) * 0.01;
        cout << value << " | " << P << " " << I << " " << D << " | " << throttle << endl;


        ruMotor->setVelocity(-throttle);
        luMotor->setVelocity(throttle);
        rdMotor->setVelocity(throttle);
        ldMotor->setVelocity(-throttle);
        if (counter == (int)(7 * 1000.0 / 32.0)) {
            cout << "---------------------- Next ------------------------------\n";
            from = 5;
            to = 10;
        }
        else if (counter == (int)(14 * 1000.0 / 32.0)) {
            from = 10;
            to = 5;
        }
        counter++;
    };

    delete robot;

    return 0;
}
