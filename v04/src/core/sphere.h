#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape {
    private:
        Point3f center;
        float radius;

    public:
        Sphere(const Point3f& _c, const float& _r, const bool& flip_n = false) : center(_c), radius(_r) {
            flip_normals = flip_n;
        }
        ~Sphere(){}

        bool intersect(const Ray &r, Surfel *sf) const override;
        bool intersect_p(const Ray &r) const override;
};

#endif