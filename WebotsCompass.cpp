#include "WebotsCompass.h"
#include "webotsController.h"

WebotsCompass::WebotsCompass(WebotsController& wc, const char* name)
{
    com = wc.getRobot()->getCompass(name);
    com->enable(TIME_STEP);
}
//Frame GPS_COM_LFM::read()
//{
//    MCVector3d pos(robot->getPosition());
//    MCMatrix3d ori(robot->getOrientation());
//    double x = ori(1), y = ori(4);
//    double len = std::sqrt(x * x + y * y);
//    x = (x / len);
//    y = (y / len);
//    Matrix2d R;
//    R << y, -x, x, y;
//    return Frame(pos, R);
//}


Vector3f WebotsCompass::read()
{
    // construct an Iframe with the north as its Y axis in the Lframe cordinates and transpose it to switch frame.
    return MCVector3d(com->getValues()).cast<float>();
}
