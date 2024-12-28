#include "Stabilizer.h"
#include <chrono>
#include <thread>

void stabilizerLoop(void *arg)
{
    Stabilizer* This = static_cast<Stabilizer*>(arg);
    Velocity twist = This->calcTwist();
    for(;;) {
        Velocity currVel = This->velocitySensor.read();
        Twist<uint16_t> command = This->controller.update(twist ,currVel);
        This->droneController.setThrottle(command[Z]);
        This->droneController.setPitch(command[W]);
        This->droneController.setYaw(command[Y]);
        This->droneController.setRoll(command[X]);
        std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
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
    droneController(_droneController),
    controller(_controller),
    velocitySensor(_velocitySensor)
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
    if(this->task == nullptr){
        this->task = new std::thread(stabilizerLoop, this);
        std::cout << "Stabilizer started!\n";
    }
}

void Stabilizer::end()
{
    if(this->task != nullptr){
        delete this->task;
        this->task = nullptr;
    }
}


