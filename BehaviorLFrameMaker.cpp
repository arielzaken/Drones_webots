#include "BehaviorLFrameMaker.h"
#include "chrono"
#include "config.h"

using namespace std::chrono;

Frame BehaviorLFrameMaker::calcLframe()
{
    static system_clock::time_point last = system_clock::now();
    Velocity vel = { 0,0,0,0 };
    for (auto i = behaviors.begin(); i != behaviors.end(); i++)
        vel += (*i)->calcBehavior();
    auto now = system_clock::now();
#ifdef WEBOTS_STEP_TIME_MS
    float dt = WEBOTS_STEP_TIME_MS;
#else
    auto dt = duration_cast<milliseconds>(now - last).count(); 
#endif // WEBOTS_STEP_TIME_MS

    last = now;
    lFrame.pos += (vel.block<3, 1>(0, 0)).cast<double>() * dt;
    lFrame.rotate(vel[3] * dt);
    return lFrame;
}

BehaviorLFrameMaker::BehaviorLFrameMaker(const Frame& lFrame)
    : lFrame(lFrame)
{
}

BehaviorHandle_t BehaviorLFrameMaker::addBehavior(Behavior_I& b)
{
    behaviors.push_back(&b);
    return --behaviors.end();
}

void BehaviorLFrameMaker::removeBehavior(BehaviorHandle_t index)
{
    behaviors.erase(index);
}


