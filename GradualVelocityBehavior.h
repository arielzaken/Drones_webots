#pragma once

#include "Behavior_I.h"
#include "chrono"

using namespace std::chrono;

class GradualVelocityBehavior : public Behavior_I {
	Velocity vel;
	uint32_t timeInterval;
	system_clock::time_point last;

	inline double F(double t);
public:
	GradualVelocityBehavior(Velocity vel, uint32_t TimeInterval);

	// Inherited via Behavior_I
	virtual Velocity calcBehavior() override;

	virtual void setup() override;

};