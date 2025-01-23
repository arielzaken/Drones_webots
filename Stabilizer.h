#pragma once
#include "Behavior_I.h"
#include "DroneController_I.h"
#include "GlobalOrientaionSensor.h"
#include "Controller_I.h"
#include "LframeMaker_I.h"
#include "config.h"
#include <thread>

typedef Controller_I<ControllSignal,Frame> Controller_t;

class Stabilizer
{
   
    DroneController_I* droneController;
    Controller_t* controller;
    GlobalOrientaionSensor* GOS;
    LframeMaker_I* Lframe;
    uint16_t baseThrottle = 1000;

    std::thread* task = nullptr;
    
    volatile bool isRunning = false;

    void stabilizerLoop();

public:
    Stabilizer(
        DroneController_I& _droneController,
        Controller_t& _controller,
        GlobalOrientaionSensor& _GOS,
        LframeMaker_I& Lframe
        );
    void setBaseThrottle(uint16_t bt) { baseThrottle = bt; }
    void begin();
    void end();
};
