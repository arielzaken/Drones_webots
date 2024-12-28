#pragma once
#include "DroneController_I.h"
#include "AltSensor.h"

#include <webots/Robot.hpp>

#include <thread>

#define TIME_STEP 32

class WebotsController : public DroneController_I {
	webots::Robot* robot;
	webots::Altimeter* alt;
	webots::Gyro* gyro;
	webots::Motor* ruMotor;
	webots::Motor* rdMotor;
	webots::Motor* luMotor;
	webots::Motor* ldMotor;
	std::thread* pThread = nullptr;
	void loop();
	uint16_t throttle = 1000;
	uint16_t pitch = 1500;
	uint16_t yaw = 1500;
	uint16_t roll = 1500;
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
	friend class WebotsAltSensor;
};

class WebotsAltSensor : public AltSensor {
	WebotsController* wc;
public:
	WebotsAltSensor(WebotsController& _wc) : wc(&_wc) {}
	// Inherited via AltSensor
	float read() override;
};