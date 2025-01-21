#include<iostream>
#include "Stabilizer.h"
#include <chrono>
#include <thread>

void Stabilizer::stabilizerLoop()
{
    std::cout << "Stabilizer started!\n";
    while(isRunning) {
        Pos lFrame = Lframe->calcLframe();
        Pos currPos = GOS->read();
        ControllSignal command = controller->update(lFrame, currPos);
        droneController->setRoll(command[X]);
        droneController->setYaw(command[Y]);
        droneController->setThrottle(command[Z]);
        droneController->setPitch(command[W]); 
    }
    std::cout << "Stabilizer stoped\n";
}

Stabilizer::Stabilizer(DroneController_I& _droneController, Controller_t& _controller, GlobalOrientaionSensor& _GOS, LframeMaker_I& _Lframe):
    droneController(&_droneController),
    controller(&_controller),
    GOS(&_GOS),
    Lframe(&_Lframe)
{
}

void Stabilizer::begin()
{
    if(!isRunning && !task){
        this->task = new std::thread(&Stabilizer::stabilizerLoop, this);
        isRunning = true;
    }
}

void Stabilizer::end()
{
    if (isRunning && task) {
        task->join();
        delete task;
        task = nullptr;
        isRunning = false;
    }
}


