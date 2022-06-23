#include <algorithm>
#include <cmath>
#include "sphere.h"
#include "vec3.h"
#include <iostream>

bool Sphere::intersect( const Ray& ray, Surfel *sf) const {
    Vector3f o = ray.origin;
    Vector3f d = ray.direction;
    Point3f c = center;
    float r = radius;
    float A = dot_vector3f(d, d);
    float B = 2*dot_vector3f((o - c), d);
    float C = dot_vector3f(o - c, o - c) - r*r;
    float delta = B*B-4*A*C;
    float time;

    if (delta >= 0) {
        float root_1 = (-B + sqrt(delta)) / (2*A);
        float root_2 = (-B - sqrt(delta)) / (2*A);

        time = std::min(root_1, root_2);
    } else {
        time = -1.0;
    }

    sf->primitive = primitive;
    sf->time = time;

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
