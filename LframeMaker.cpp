#include "LframeMaker.h"
#include <chrono>

using namespace std::chrono;

LframeMaker::LframeMaker()
{
    memset(behaviors, 0, sizeof(Behavior_I*) * STABILIZER_NUM_OF_BEHAVIORS);
    numOfBehaviors = 0;
}

uint8_t LframeMaker::addBehavior(Behavior_I& behavior)
{
    if (numOfBehaviors <= STABILIZER_NUM_OF_BEHAVIORS - 1) {
        for (uint8_t i = 0; i < STABILIZER_NUM_OF_BEHAVIORS; i++) {
            if (!behaviors[i]) {
                behaviors[i] = &behavior;
                behavior.setup();
                numOfBehaviors++;
                return i;
            }
        }
    }
    return UINT8_MAX;
}

void LframeMaker::removeBehavior(uint8_t discriptor)
{
    behaviors[discriptor] = nullptr;
}

Pos LframeMaker::calcLframe()
{
    static system_clock::time_point last = system_clock::now();
    Velocity res = { 0, 0, 0, 0 };
    for (size_t i = 0; i < numOfBehaviors; i++) {
        if (behaviors[i] != nullptr) {
            res += behaviors[i]->calcBehavior();
        }
    }
    system_clock::time_point now = system_clock::now();
    Lframe += res * duration_cast<milliseconds>(now - last).count();
    last = now;
    return Lframe;
}
