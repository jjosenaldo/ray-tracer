#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    private:
        Point3f origin;
        Vector3f direction;
    public:
        Ray(const Point3f& o, const Vector3f& d );
        Vector3f operator-(float t) const;
};

#endif