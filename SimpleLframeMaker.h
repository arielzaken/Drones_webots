#pragma once

#include "LframeMaker_I.h"
#include "Primitives.h"

class SimpleLframeMaker : public LframeMaker_I
{
	Frame lFrame;
public:
	SimpleLframeMaker(const Frame& lFrame);

	// Inherited via LframeMaker_I
	Frame calcLframe() override;

	void setLframe(Frame pos) { lFrame = pos; }
};