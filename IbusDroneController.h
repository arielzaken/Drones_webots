#include "DroneController/DroneController_I.h"
#include "Protocol/ibus/ibus.h"
class IbusDroneController : public DroneController_I{
    virtual void setThrottle(uint16_t throttle)  override;
    virtual void setPitch(uint16_t pitch)  override;
    virtual void setYaw(uint16_t yaw) override;
    virtual void setRoll(uint16_t roll) override;
    virtual void setAUX( uint16_t channle ,uint16_t auxValue) override;

    virtual void arm() override;
    virtual void disarm() override;
    virtual void disable() override;
    virtual void enable() override;
};