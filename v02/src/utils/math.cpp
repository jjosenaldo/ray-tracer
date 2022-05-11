#include "math.h"

ostream &operator<<(ostream &os, const Point2f &point)
{
    os << "Point2(" << point[0] << "," << point[1] << ")";

    return os;
}