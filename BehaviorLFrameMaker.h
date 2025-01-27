#pragma once

#include "Behavior_I.h"
#include "LframeMaker_I.h"
#include "Primitives.h"
#include "list"
#include "mutex"

using BehaviorHandle_t = int;

class BehaviorLFrameMaker : public LframeMaker_I 
{
	Frame lFrame;
	std::list<Behavior_I*> behaviors;
	std::mutex mtx;
public:
	BehaviorLFrameMaker() = default;
	BehaviorLFrameMaker(const Frame& lFrame);
	void addBehavior(Behavior_I& b);
	void removeBehavior(Behavior_I& b);
	// Inherited via LframeMaker_I
	Frame calcLframe() override;
};