#pragma once

#include <Eigen/Dense>

enum{ X, Y, Z, W };

template <typename T>
using Vec3D = Eigen::Vector<T, 3>;

template <typename T>
using Vec2D = Eigen::Vector<T, 2>; 

using ControllSignal = Eigen::Vector<uint16_t, 4>;

using Pos = Eigen::Vector<float, 4>;

using Velocity = Pos;

using Acceleration = Pos;

using Eigen::Matrix3f;
using Eigen::Matrix3d;

using MCMatrix3d = Eigen::Map<const Eigen::Matrix<double, 3, 3, Eigen::RowMajor>>;
using MCMatrix3f = Eigen::Map<const Eigen::Matrix<float, 3, 3, Eigen::RowMajor>>;
using MCVector3f = Eigen::Map<const Eigen::Vector3f>;
using MCVector3d = Eigen::Map<const Eigen::Vector3d>;

using MMatrix3d = Eigen::Map<Eigen::Matrix<double, 3, 3, Eigen::RowMajor>>;
using MMatrix3f = Eigen::Map<Eigen::Matrix<float, 3, 3, Eigen::RowMajor>>;
using MVector3f = Eigen::Map<Eigen::Vector3f>;
using MVector3d = Eigen::Map<Eigen::Vector3d>;
