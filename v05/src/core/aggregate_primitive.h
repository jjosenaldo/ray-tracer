#ifndef AGGREGATE_PRIMITIVE_H
#define AGGREGATE_PRIMITIVE_H

#include "primitive.h"

class AggregatePrimitive: public Primitive {
    private:
        std::vector<Primitive*> primitives;

    public:
        using Primitive::intersect;
        using Primitive::intersect_p;
        using Primitive::get_material;

        AggregatePrimitive(std::vector<Primitive*> p_primitives): primitives(p_primitives) {  }
        Material* get_material();
        void add_primitive(Primitive* primitive);
        bool intersect( const Ray& r, Surfel *sf, float min_t, float max_t );
        bool intersect_p( const Ray& r);
};

#endif