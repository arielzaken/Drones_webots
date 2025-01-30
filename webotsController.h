#pragma once
#include "DroneController_I.h"
#include <webots/Robot.hpp>
#include <thread>
#include "PID.h" 
#include "config.h"

class WebotsController : public DroneController_I {
	webots::Robot* robot;
	webots::Gyro* gyro;
	webots::Motor* ruMotor;
	webots::Motor* rdMotor;
	webots::Motor* luMotor;
	webots::Motor* ldMotor;
	std::thread* pThread = nullptr;
	bool isRunning = false;
	void loop();
	uint16_t throttle = 1000;
	uint16_t pitch = 1500;
	uint16_t yaw = 1500;
	uint16_t roll = 1500;

	PID yawPID;
	PID rollPID;
public:
	WebotsController();
	~WebotsController();
	// Inherited via DroneController_I
	void setThrottle(uint16_t throttle) override;
	void setPitch(uint16_t pitch) override;
	void setYaw(uint16_t yaw) override;
	void setRoll(uint16_t roll) override;
	void setAUX(uint16_t channle, uint16_t auxValue) override;
	void arm() override;
	void disarm() override;
	void disable() override;
	void enable() override;
	void wait();
	bool checkIsRunning() const { return isRunning; }
	webots::Robot* getRobot() { return robot; };
};

