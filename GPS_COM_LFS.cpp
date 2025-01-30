#include "GPS_COM_LFS.h"

GPS_COM_LFS::GPS_COM_LFS(GPS_I& gps, Compass_I& com) : gps(&gps), com(&com){}

Frame GPS_COM_LFS::read()
{
    return Frame(gps->read().block<3,1>(0,0), Matrix2f().Zero()); // << steaming hot garbege...
}
