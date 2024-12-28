#pragma once
#include "Primitives.h"
#include <stdint.h>
class Behavior_I
{
public:
    virtual Velocity calcBehavior() = 0;
    virtual void setup() = 0;
};