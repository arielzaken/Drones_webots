#include "HoverBehavior.h"
#include "Primitives.h"

Velocity HoverBehavior::calcBehavior()
{
    uint16_t alt = altSensor->read();
    int16_t diff = (int16_t)(requiredAlt - alt);
    if(diff * diff > 0.01){ // the fhreshold is 10, 100 for skiping the sqrt
        return {0, 0, (float)diff, 0};
    }
    return {0, 0, 0, 0};
}

void HoverBehavior::setup()
{

}
