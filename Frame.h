#pragma once

#include <Eigen/dense>
#include <iostream>

using Eigen::Vector3f;
using Eigen::Matrix2f;

struct Frame {
	Vector3f pos;
	Matrix2f ori;
	Frame();
	Frame(Vector3f pos, double angle);

	bool operator==(const Frame& other) const
	{
		return pos == other.pos && ori == other.ori;
	}

	Frame(const Vector3f& pos, const Matrix2f& ori)
		: pos(pos), ori(ori)
	{
	}

	void setOri(double ang);
	void rotate(double ang);

	friend std::ostream& operator<<(std::ostream& o, const Frame& frame);
};