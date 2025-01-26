#pragma once

#include <Eigen/dense>
#include <iostream>

using Eigen::Vector3d;
using Eigen::Matrix2d;

struct Frame {
	Vector3d pos;
	Matrix2d ori;
	Frame();
	Frame(Vector3d pos, double angle);

	bool operator==(const Frame& other) const
	{
		return pos == other.pos && ori == other.ori;
	}

	Frame(const Vector3d& pos, const Matrix2d& ori)
		: pos(pos), ori(ori)
	{
	}

	void setOri(double ang);
	void rotate(double ang);

	friend std::ostream& operator<<(std::ostream& o, const Frame& frame);
};