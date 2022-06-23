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
    int size = primitives.size(), best_idx = -1;
    Surfel* current = new Surfel[size];
    float best_t;

    for (int i=0; i<size; i++) {
        if (primitives[i]->intersect(ray, &current[i])) {
            if (best_idx == -1 || current[i].time < best_t) {
                best_idx = i;
				best_t = current[i].time;
            }
        }
    }

    if (best_idx == -1) return false;
    sf->copy_from(&current[best_idx]);
    delete current;
    
    return true;
}

bool AggregatePrimitive::intersect_p( const Ray& ray) {
    for (Primitive* p: primitives) {
        if (p->intersect_p(ray)) {
            return true;
        }
    }

    return false;
}
