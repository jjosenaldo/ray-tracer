#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive {
    private:
        Point3f center;
        float radius;
    public:
        Sphere(const Point3f& _c, const float& _r, Material* mat) : center(_c), radius{_r} {
            material = mat;
        }
        ~Sphere(){}

        bool intersect(const Ray &r, const Surfel *sf) const override;
        bool intersect_p(const Ray &r) const override;
};

#endif