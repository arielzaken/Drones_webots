#include "Stabilizer.h"
#include <chrono>
#include <thread>

void Stabilizer::stabilizerLoop()
{
    std::cout << "Stabilizer started!\n";
    while(isRunning) {
        Velocity twist = calcTwist();
        Velocity currVel = velocitySensor->read();
        Twist<uint16_t> command = controller->update(twist ,currVel);
        droneController->setThrottle(command[Z]);
        droneController->setPitch(command[W]);
        droneController->setYaw(command[Y]);
        droneController->setRoll(command[X]);
        //std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
    std::cout << "Stabilizer stoped\n";
}

Velocity Stabilizer::calcTwist()
{
    Velocity res;
    for (size_t i = 0; i < numOfBehaviors; i++){
        if(behaviors[i] != nullptr){
            res += behaviors[i]->calcBehavior();
        }
    }
    return res;
}

Stabilizer::Stabilizer(
    DroneController_I &_droneController,
    Controller_t &_controller,
    VelocitySensor &_velocitySensor) : 
    droneController(&_droneController),
    controller(&_controller),
    velocitySensor(&_velocitySensor)
{
    memset(behaviors, 0, sizeof(Behavior_I*) * STABILIZER_NUM_OF_BEHAVIORS);
    numOfBehaviors = 0;
}

uint8_t Stabilizer::addBehavior(Behavior_I &behavior)
{
    if(numOfBehaviors <= STABILIZER_NUM_OF_BEHAVIORS-1){
        for(size_t i = 0; i < STABILIZER_NUM_OF_BEHAVIORS; i++){
            if(!behaviors[i]){
                behaviors[i] = &behavior;
                behavior.setup();
                numOfBehaviors++;
                return i;
            }
        }
    }
    return 0;
}

void Stabilizer::removeBehavior(uint8_t discriptor)
{
    behaviors[discriptor] = nullptr;
}

void Stabilizer::begin()
{
    if(!isRunning && !task){
        this->task = new std::thread(stabilizerLoop, this);
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


