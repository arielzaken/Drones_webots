#include "SimpleLframeMaker.h"

Frame SimpleLframeMaker::calcLframe()
{
    return Lframe;
}


SimpleLframeMaker::SimpleLframeMaker(const Frame& Lframe)
    : Lframe(Lframe)
{
}
