#pragma once
#include "Operator.h"

class Operator;

class State_I{
public:
    virtual void handle(Operator* this_) = 0;
};

class GroundState : public State_I{
    virtual void handle(Operator* this_)  override;
};

class CheckState : public State_I{
    virtual void handle(Operator* this_) override;
};

class TakeoffState : public State_I{
    virtual void handle(Operator* this_) override;
};

class TransitState : public State_I{
    virtual void handle(Operator* this_) override;
};

class LandState : public State_I{
    virtual void handle(Operator* this_) override;
};