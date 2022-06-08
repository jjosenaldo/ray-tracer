#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "material.h"
#include "ray.h"
#include "surfel.h"

class Primitive {
    public:
        virtual ~Primitive(){};
        virtual bool intersect( const Ray& r, Surfel *sf ) = 0;
        // Simpler and faster version of intersection that only return true/false.
        // It does not compute the hit point information.
        virtual bool intersect_p( const Ray& r) = 0;
        //virtual Bounds3f world_bounds() const = 0;
        virtual Material* get_material() = 0;
};

#endif