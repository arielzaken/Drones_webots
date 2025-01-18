#pragma once
#include "DroneController_I.h"
#include "AltSensor.h"
#include "VelocitySensor.h"

#include <webots/Supervisor.hpp>

#include <thread>

#include "config.h"

class WebotsController : public DroneController_I {
	webots::Supervisor* robot;
	webots::Altimeter* alt;
	webots::InertialUnit* imu;
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
	bool isRunning() { return pThread != nullptr; }
	friend class WebotsAltSensor;
	friend class WebotsVelocitySensor;
};

class WebotsAltSensor : public AltSensor {
	WebotsController* wc;
public:
	WebotsAltSensor(WebotsController& _wc) : wc(&_wc) {}
	// Inherited via AltSensor
	float read() override;
};

class WebotsVelocitySensor : public VelocitySensor {
	WebotsController* wc;
public:
	WebotsVelocitySensor(WebotsController& _wc) : wc(&_wc) {}
	// Inherited via AltSensor
	Velocity read() override;
};