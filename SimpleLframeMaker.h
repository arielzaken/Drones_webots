#pragma once

#include "LframeMaker_I.h"
#include "Primitives.h"

class SimpleLframeMaker : public LframeMaker_I
{
	Frame Lframe;
public:
	SimpleLframeMaker(const Frame& Lframe);

	// Inherited via LframeMaker_I
	Frame calcLframe() override;

	void setLframe(Frame pos) { Lframe = pos; }
};