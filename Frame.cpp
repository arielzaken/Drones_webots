#include "Frame.h"

Frame::Frame()
{
	pos.Zero();
	ori << 1,0,0,1;
}

Frame::Frame(Vector3f pos, double angle) :
	pos(pos)
{
	setOri(angle);
}

void Frame::setOri(double ang)
{
	float c = (float)cos(ang);
	float s = (float)sin(ang);
	ori <<
		c, -s,
		s, c;
}

void Frame::rotate(double ang)
{
	float c = (float)cos(ang);
	float s = (float)sin(ang);
	Matrix2f R;
	R <<
		c, s,
		-s, c;
	ori = R * ori;
}

std::ostream& operator<<(std::ostream& o, const Frame& frame)
{
	o << "pos: \n" << frame.pos << std::endl;
	o << "ori: \n" << frame.ori << std::endl;
	return o;
}
