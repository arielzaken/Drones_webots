#pragma once

#include "Behavior_I.h"
#include "DistanceSensor_I.h"


class ObsticalAvoidanseBehavior : public Behavior_I {
	DistanceSensor_I* distanseArray[8];
public:
	ObsticalAvoidanseBehavior(DistanceSensor_I** distanceArray);
	// Inherited via Behavior_I
	Velocity calcBehavior() override;
	void setup() override;
};