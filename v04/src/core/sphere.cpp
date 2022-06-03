#include "sphere.h"
#include "vec3.h"

bool Sphere::intersect( const Ray& r, const float& t_hit, const Surfel *sf) const {
    // TODO
    return true;
}

bool Sphere::intersect_p( const Ray& ray) const {
    auto o = ray.origin;
    auto d = ray.direction;
    auto c = center;
    auto r = radius;
    auto A = dot_vector3f(d, d);
    auto B = dot_vector3f(2*(o - c), d);
    auto C = dot_vector3f(o - c, o - c) - r*r;
    auto delta = B*B-4*A*C;

    return delta >= 0;
}