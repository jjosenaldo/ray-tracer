#include "geometric_primitive.h"

bool GeometricPrimitive::intersect(const Ray& r, const Surfel *sf) const {
    // tá mas pelo diagrama GeometricPrimitive n tem membro time
    // então quem q recebe essa informação do time? 
    
    float time_hit = 0;
    return shape->intersect(r, time_hit, sf);
}

bool GeometricPrimitive::intersect_p(const Ray& r) const {
    return shape->intersect_p(r);
}

Material* GeometricPrimitive::get_material(void) const {
    return material;
}

void GeometricPrimitive::set_material(Material* &mat) {
    material = mat;
}

