#pragma once

#include "Primitives.h"
#include "Behavior_I.h"
#include "config.h"

class LframeMaker
{
    Behavior_I* behaviors[STABILIZER_NUM_OF_BEHAVIORS];
    uint8_t numOfBehaviors;
	Pos Lframe;
public:
    LframeMaker();
    /**
     * add a new behavior mid-run to the stablizer
     * @param behavior the new behavior to add
     * @return a discriptor for the behavior that was added
     */
    uint8_t addBehavior(Behavior_I& behavior);
    /**
     * remove a behavior mid-run from the stablizer
     * @param discriptor the discriptor we got from the addBehavior method to remove the behavior.
     */
    void removeBehavior(uint8_t discriptor);

    Pos calcLframe();
};

