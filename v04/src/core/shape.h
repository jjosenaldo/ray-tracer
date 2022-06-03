#ifndef SHAPE_H
#define SHAPE_H

#include "ray.h"
#include "surfel.h"

class Shape {
    protected:
        bool flip_normals = false;

    public:
        Shape(){}
        Shape(const bool& flip_n) : flip_normals(flip_n) {}
        ~Shape(){}

        //virtual Bounds3f world_bounds() const = 0;
        virtual bool intersect(const Ray &r, const float& t_hit, const Surfel *sf) const = 0;
        virtual bool intersect_p(const Ray &r) const = 0;
};

#endif