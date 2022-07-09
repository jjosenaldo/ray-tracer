#include "geometric_primitive.h"

bool GeometricPrimitive::intersect(const Ray& r, Surfel *sf, float min_t, float max_t) {
    return shape->intersect(r, sf, min_t, max_t);
}

bool GeometricPrimitive::intersect_p(const Ray& r) {
    return shape->intersect_p(r);
}

Material* GeometricPrimitive::get_material() {
    return material;
}

void GeometricPrimitive::set_material(Material* &mat) {
    material = mat;
}

