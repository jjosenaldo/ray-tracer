#include "ray.h"

Ray::Ray(const Point3f& o, const Vector3f& d ) : origin{o}, direction{d} { }

Vector3f Ray::operator-(float t) const {
    return origin + t * direction;
}