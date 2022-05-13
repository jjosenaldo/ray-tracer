#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        Ray(const Point3f& o, const Vector3f& d );
        Point3f origin;
        Vector3f direction;
        Vector3f operator-(float t) const;
};

#endif