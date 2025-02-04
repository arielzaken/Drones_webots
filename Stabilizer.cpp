#include<iostream>
#include "Stabilizer.h"
#include <chrono>
#include <thread>

void Stabilizer::stabilizerLoop()
{
    std::cout << "Stabilizer started!\n";
    while(isRunning) {
        Frame currPos = GOS->read();
        Frame lFrame = lFrameMaker->calcLframe();
        ControllSignal command = controller->update(lFrame, currPos);
        command.block<2, 1>(0, 0) = (currPos.ori.transpose() * (command.block<2, 1>(0, 0)).cast<float>()).cast<int16_t>();
        droneController->setRoll(1500 + command[0]);
        droneController->setYaw(1500 + command[1]);
        droneController->setThrottle(baseThrottle + command[2]);
        droneController->setPitch(1500 + command[3]); 
    }
    std::cout << "Stabilizer stoped\n";
}

Stabilizer::Stabilizer(DroneController_I& _droneController, Controller_t& _controller, LFS_I& _GOS, LframeMaker_I& _Lframe):
    droneController(&_droneController),
    controller(&_controller),
    GOS(&_GOS),
    lFrameMaker(&_Lframe)
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
        isRunning = false;
        task->join();
        delete task;
        task = nullptr;
    }
}


