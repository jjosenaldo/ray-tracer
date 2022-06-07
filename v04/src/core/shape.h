#ifndef SHAPE_H
#define SHAPE_H

#include "geometric_primitive.h"
#include "ray.h"
#include "surfel.h"

class GeometricPrimitive;
class Shape {
    protected:
        bool flip_normals = false;
        GeometricPrimitive* primitive = nullptr;

    public:
        Shape(){}
        Shape(const bool& flip_n) : flip_normals(flip_n) {}
        ~Shape(){}

        //virtual Bounds3f world_bounds() const = 0;
        virtual bool intersect(const Ray &r, float& t_hit, Surfel *sf) const = 0;
        virtual bool intersect_p(const Ray &r) const = 0;
};

#endif