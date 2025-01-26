#include "SimpleLframeMaker.h"

Frame SimpleLframeMaker::calcLframe()
{
    return lFrame;
}


SimpleLframeMaker::SimpleLframeMaker(const Frame& lFrame)
    : lFrame(lFrame)
{
}
