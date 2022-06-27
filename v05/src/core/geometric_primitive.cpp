#include "geometric_primitive.h"

bool GeometricPrimitive::intersect(const Ray& r, Surfel *sf) {
    return shape->intersect(r, sf);
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

