#pragma once

#include "LframeMaker_I.h"
#include "Primitives.h"

class SimpleLframeMaker : public LframeMaker_I
{
	Pos Lframe;
public:
	SimpleLframeMaker(const Pos& Lframe);

	// Inherited via LframeMaker_I
	Pos calcLframe() override;

	void setLframe(Pos pos) { Lframe = pos; }
};