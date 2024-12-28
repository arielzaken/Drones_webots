#include "Operator.h"

void Operator::setState(State_I *_state)
{
    state = _state;
}

void Operator::setStablizer(Stabilizer *newStablizer)
{
    itsStablizer = newStablizer;
}

Stabilizer *Operator::getStablizer()
{
    return itsStablizer;
}
