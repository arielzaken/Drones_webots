#pragma once
#include "States.h"
#include "Stabilizer.h"
class State_I;
/**
 * this class represents the context in the state design pattern
 */
class Operator{
    State_I* state;
    Stabilizer* itsStablizer;
public:
    void setState(State_I* state);
    void setStablizer(Stabilizer* newStablizer);
    Stabilizer* getStablizer();
};