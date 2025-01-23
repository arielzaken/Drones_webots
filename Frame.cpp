#include "Frame.h"

Frame::Frame()
{
	pos.Zero();
	ori.Identity();
}

Frame::Frame(Vector3d pos, double angle) :
	pos(pos)
{
	setOri(angle);
}

void Frame::setOri(double ang)
{
	double c = cos(ang);
	double s = sin(ang);
	ori <<
		c, -s,
		s, c;
}

std::ostream& operator<<(std::ostream& o, const Frame& frame)
{
	o << "pos: \n" << frame.pos << std::endl;
	o << "ori: \n" << frame.ori << std::endl;
	return o;
}
