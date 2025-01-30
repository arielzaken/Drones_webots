#include "WebotsGPS.h"
#include "webotsController.h"


WebotsGPS::WebotsGPS(WebotsController& _wc, const char* name)
{
    gps = _wc.getRobot()->getGPS(name);
    gps->enable(TIME_STEP);
}

Vector4f WebotsGPS::read()
{
    const double* temp = gps->getValues();
    return Vector4f((float)temp[0], (float)temp[1], (float)temp[2], gps->getSpeed());
}
