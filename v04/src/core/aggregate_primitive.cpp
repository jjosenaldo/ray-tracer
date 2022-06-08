#include <limits>

#include "aggregate_primitive.h"
#include "error.h"

Material* AggregatePrimitive::get_material() {
    RT3_ERROR("Aggregates are not allowed to have materials associated with them.");

    return nullptr;
}

void AggregatePrimitive::add_primitive(Primitive* primitive) {
    primitives.push_back(primitive);
}

bool AggregatePrimitive::intersect( const Ray& ray, Surfel *sf ) {
    Surfel* best_surfel;
    float best_t = std::numeric_limits<float>::min();
    
    for (Primitive* p: primitives) {
        Surfel current_surfel;

        if (p->intersect(ray, &current_surfel)) {
            if (!best_surfel || (current_surfel.time >= 0 && current_surfel.time < best_surfel->time)) {
                best_surfel = &current_surfel;
            }
        }
    }

    sf->copy_from(best_surfel);

    return !best_surfel;
}

bool AggregatePrimitive::intersect_p( const Ray& ray) {
    for (Primitive* p: primitives) {
        if (p->intersect_p(ray)) {
            return true;
        }
    }

    return false;
}