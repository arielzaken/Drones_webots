#include "GPS_COM_LFS.h"

GPS_IMU_LFS::GPS_IMU_LFS(GPS_I& gps, IMU_I& imu) : gps(&gps), imu(&imu){}

Frame GPS_IMU_LFS::read()
{
    // optimize me!!!!! plz :<
    Vector3f ang = imu->read();
    Matrix3f ori;
    ori = 
        Eigen::AngleAxisf(ang[0], Vector3f::UnitX()) * // E
        Eigen::AngleAxisf(ang[1], Vector3f::UnitY()) * // N
        Eigen::AngleAxisf(ang[2], Vector3f::UnitZ());  // U
    double x = ori(1), y = ori(4);
    double len = std::sqrt(x * x + y * y);
    x = (x / len);
    y = (y / len);
    Matrix2f R;
    R << y, -x, x, y;
    return Frame(gps->read().block<3, 1>(0, 0), R);
}
