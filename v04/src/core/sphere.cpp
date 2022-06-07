#include <algorithm>
#include <cmath>
#include "sphere.h"
#include "vec3.h"

bool Sphere::intersect( const Ray& ray, float& t_hit, Surfel *sf) const {
    auto o = ray.origin;
    auto d = ray.direction;
    auto c = center;
    auto r = radius;
    auto A = dot_vector3f(d, d);
    auto B = dot_vector3f(2*(o - c), d);
    auto C = dot_vector3f(o - c, o - c) - r*r;
    auto delta = B*B-4*A*C;

    if (delta >= 0) {
        auto t_1 = (dot_vector3f((o-c)*-1, d) + sqrt( dot_vector3f(o-c,d)*dot_vector3f(o-c,d) - ( dot_vector3f(d,d)*dot_vector3f(o-c,o-c) )  -r*r  )) / (dot_vector3f(d,d));
        auto t_2 = (dot_vector3f((o-c)*-1, d) - sqrt( dot_vector3f(o-c,d)*dot_vector3f(o-c,d) - ( dot_vector3f(d,d)*dot_vector3f(o-c,o-c) )  -r*r  )) / (dot_vector3f(d,d));

        return std::min(t_1, t_2);
    } else {
        t_hit = -1.0;
    }

    sf->primitive = primitive;

    return delta >= 0;
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