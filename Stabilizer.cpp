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
        droneController->setRoll(command[0]);
        droneController->setYaw(command[1]);
        droneController->setThrottle(command[2]);
        droneController->setPitch(command[3]); 
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


