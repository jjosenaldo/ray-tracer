#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        Point3f origin;
        Vector3f direction;

        Ray(const Point3f& o, const Vector3f& d );
	~Ray(){}
        Vector3f operator()(float t) const;
};

#endif
