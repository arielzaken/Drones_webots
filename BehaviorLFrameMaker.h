#pragma once

#include "Behavior_I.h"
#include "LframeMaker_I.h"
#include "Primitives.h"
#include "vector"
#include "mutex"

using BehaviorHandle_t = std::vector<Behavior_I*>::iterator;

class BehaviorLFrameMaker : public LframeMaker_I 
{
	Frame lFrame;
	std::vector<Behavior_I*> behaviors;
	std::mutex mtx;
public:
	BehaviorLFrameMaker() = default;
	BehaviorLFrameMaker(const Frame& lFrame);
	BehaviorHandle_t addBehavior(Behavior_I& b);
	void removeBehavior(BehaviorHandle_t index);
	// Inherited via LframeMaker_I
	Frame calcLframe() override;
};