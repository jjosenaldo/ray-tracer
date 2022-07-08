#include "plane.h"

Plane::Plane(Material* m, const Point3f& _p1, const Point3f& _p2, const Point3f& _p3): material(m), p1(_p1), p2(_p2), p3(_p3) {
    n = normalize_vector3f(cross_vector3f(p1 - p2, p1 - p3));
}


bool Plane::intersect( const Ray& r, Surfel *sf ) {
    auto denominator = dot_vector3f(n, r.direction);

    if (denominator == 0) {
        return false;
    }

    auto numerator = dot_vector3f(n, p1-r.origin);
    auto t = numerator / denominator;
    auto p = r(t);

    if (!same_side_as(p1, p2, p3, p) || !same_side_as(p2, p3, p1, p) || !same_side_as(p1, p3, p2, p)) {
        return false;
    }

    sf->primitive = this;
    sf->time = t;
    sf->wo = r.origin - r.direction;
    sf->p = p;
    sf->n = n;

    return true;
}

bool Plane::intersect_p( const Ray& r) {
    auto surfel = Surfel();
    return intersect(r, &surfel);
}

Material* Plane::get_material() {
    return material;
}

void Plane::set_material(Material*& mat) {
    material = mat;
}

bool same_side_as(Point3f p1, Point3f p2, Point3f p3, Point3f p) {
    Vector3f proj_p = proj_vector3f(p-p1, p2-p1);
    Point3f p_prime = proj_p + p1;
    Vector3f p_prime_to_p = p - p_prime;

    Vector3f proj_p3 = proj_vector3f(p3-p1, p2-p1);
    Point3f p3_prime = proj_p3 + p1;
    Vector3f p3_prime_to_p3 = p3 - p3_prime;

    auto cossine = dot_vector3f(p_prime_to_p, p3_prime_to_p3) / (norm_vector3f(p_prime_to_p)*norm_vector3f(p3_prime_to_p3));

    return cossine > 0.999; // cossine == 1
}