#include "GPS_COM_LFS.h"

GPS_IMU_LFS::GPS_IMU_LFS(GPS_I& gps, IMU_I& imu) : gps(&gps), imu(&imu){}

Frame GPS_IMU_LFS::read()
{
    Vector3f ang = imu->read();
    Matrix3f R;
    R = Eigen::AngleAxisf(ang[0], Vector3f::UnitX()) * // E
        Eigen::AngleAxisf(ang[1], Vector3f::UnitY()) * // N
        Eigen::AngleAxisf(ang[2], Vector3f::UnitZ());  // U
    return Frame(gps->read().block<3,1>(0,0), R.block<2,2>(0,0)); // << steaming hot garbege...
}
