#include "math.h"

ostream &operator<<(ostream &os, const Point2 &point)
{
    os << "Point2(" << point.x << "," << point.y << ")";

    return os;
}