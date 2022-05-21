#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive {
    private:
        Point3f center;
        float radius;
    public:
        Sphere(const Point3f& _c, const float& _r) : center(_c), radius{_r} { /* empty */ }
        ~Sphere(){}

        bool intersect(const Ray &r, const Surfel *sf) const override;
        bool intersect_p(const Ray &r) const override;
};

#endif