#include <algorithm>
#include <cmath>
#include "sphere.h"
#include "vec3.h"

bool Sphere::intersect( const Ray& ray, Surfel *sf) const {
    Vector3f o = ray.origin;
    Vector3f d = ray.direction;
    Point3f c = center;

    float r = radius;
    float A = dot_vector3f(d, d);
    float B = 2*dot_vector3f((o - c), d);
    float C = dot_vector3f(o - c, o - c) - r*r;
    float delta = B*B-4*A*C;

    float time = -1.0;

    if (delta > 0) {
        float root_1 = (-B + sqrt(delta)) / (2*A);
        float root_2 = (-B - sqrt(delta)) / (2*A);

        time = std::min(root_1, root_2);
    }
	else if(delta == 0) time = -B/(2*A);

    sf->primitive = primitive;
    sf->time = time;
    sf->wo = o - d;
    sf->p = ray(time);
    sf->n = normalize_vector3f(sf->p - c);

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
