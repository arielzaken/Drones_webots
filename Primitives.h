#pragma once

#include <Eigen/Dense>
#include "Frame.h"

enum{ X, Y, Z };

using Eigen::Vector2d;
using Eigen::Vector3d;

using ControllSignal = Eigen::Vector<int16_t, 4>;

using Pos = Eigen::Vector<float, 5>;
using Velocity = Eigen::Vector<float, 4>;


using Eigen::Matrix3f;
using Eigen::Matrix3d;

using Eigen::Matrix2f;
using Eigen::Matrix2d;

using MCMatrix3d = Eigen::Map<const Eigen::Matrix<double, 3, 3, Eigen::RowMajor>>;
using MCMatrix3f = Eigen::Map<const Eigen::Matrix<float, 3, 3, Eigen::RowMajor>>;
using MCVector3f = Eigen::Map<const Eigen::Vector3f>;
using MCVector3d = Eigen::Map<const Eigen::Vector3d>;

using MMatrix3d = Eigen::Map<Eigen::Matrix<double, 3, 3, Eigen::RowMajor>>;
using MMatrix3f = Eigen::Map<Eigen::Matrix<float, 3, 3, Eigen::RowMajor>>;
using MVector3f = Eigen::Map<Eigen::Vector3f>;
using MVector3d = Eigen::Map<Eigen::Vector3d>;
