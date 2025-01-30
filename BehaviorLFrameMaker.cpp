#include "BehaviorLFrameMaker.h"
#include "chrono"
#include "config.h"

using namespace std::chrono;

Frame BehaviorLFrameMaker::calcLframe()
{
    static system_clock::time_point last = system_clock::now();
    Velocity vel = { 0,0,0,0 };
    mtx.lock();
    for (auto i = behaviors.begin(); i != behaviors.end(); i++)
        vel += (*i)->calcBehavior();
    mtx.unlock();
    auto now = system_clock::now();
#ifdef WEBOTS_STEP_TIME_MS
    float dt = (float)WEBOTS_STEP_TIME_MS;
#else
    auto dt = duration_cast<milliseconds>(now - last).count(); 
#endif // WEBOTS_STEP_TIME_MS

    last = now;
    lFrame.pos += vel.block<3, 1>(0, 0) * dt;
    lFrame.rotate(vel[3] * dt);
    std::cout << lFrame << std::endl;
    return lFrame;
}

BehaviorLFrameMaker::BehaviorLFrameMaker(const Frame& lFrame)
    : lFrame(lFrame)
{
}

void BehaviorLFrameMaker::addBehavior(Behavior_I& b)
{
    b.setup();
    mtx.lock();
    behaviors.push_back(&b);
    mtx.unlock();
}

void BehaviorLFrameMaker::removeBehavior(Behavior_I& b)
{
    mtx.lock();
    behaviors.remove(&b);
    mtx.unlock();
}


