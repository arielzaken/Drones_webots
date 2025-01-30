#include "GradualVelocityBehavior.h"
#include "chrono"
using namespace std::chrono;

GradualVelocityBehavior::GradualVelocityBehavior(Velocity vel, uint32_t timeInterval) : vel(vel), timeInterval(timeInterval), last(system_clock::now())
{
}

inline double GradualVelocityBehavior::F(double t) {
    static double temp1 = 6.0 / (timeInterval * timeInterval);
    static double temp2 = -temp1 / timeInterval;
    return t * (temp1 + temp2 * t);
}

Velocity GradualVelocityBehavior::calcBehavior()
{
    auto now = system_clock::now();
    double time = duration_cast<milliseconds>(now - last).count() / 1000.0; 
    if (time <= timeInterval)
        return vel * F(time);
    return {0,0,0,0};
}

void GradualVelocityBehavior::setup()
{
    last = system_clock::now();
}
