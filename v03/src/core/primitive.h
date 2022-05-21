#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ray.h"
#include "surfel.h"
//#include "material.h"

class Primitive {
    private:
        // Not necessary for now
        //std::shared_ptr<Material> material;

    public:
        virtual ~Primitive(){};
        virtual bool intersect( const Ray& r, const Surfel *sf ) const = 0;
        // Simpler and faster version of intersection that only return true/false.
        // It does not compute the hit point information.
        virtual bool intersect_p( const Ray& r) const = 0;
        //virtual const Material * get_material(void) const = {return material; }
};

#endif