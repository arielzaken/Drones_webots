#include "HoverBehavior.h"
#include "Primitives.h"

#define EPS 0.0000001
#define ZERO(x){abs(x) < EPS ? 0.0f : x}

void HoverBehavior::SetRequiredAlt(float reqAlt)
{
    requiredAlt = reqAlt;
}

Velocity HoverBehavior::calcBehavior()
{
    return {0, 0, ZERO(requiredAlt - altSensor->read()), 0};
}

void HoverBehavior::setup()
{

}
