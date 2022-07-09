#include <algorithm>
#include <cmath>
#include "sphere.h"
#include "vec3.h"

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

bool Sphere::intersect( const Ray& ray, Surfel *sf, float min_t, float max_t) const {
    Vector3f o = ray.origin;
    Vector3f d = ray.direction;
    Point3f c = center;

    float r = radius;
    float A = dot_vector3f(d, d);
    float B = 2*dot_vector3f((o - c), d);
    float C = dot_vector3f(o - c, o - c) - r*r;
    float delta = B*B-4*A*C;

    float time = -1.0; 
    string s;

    if (delta > 0) {
        float root_1 = (-B + sqrt(delta)) / (2*A);
        float root_2 = (-B - sqrt(delta)) / (2*A);

        float min_root = std::min(root_1, root_2);
        float max_root = std::max(root_1, root_2);

        if (max_root < min_t || min_root > max_t) {
            return false;
        }

        if (min_root < min_t) {
            time = max_root;
        } else {
            time = min_root;
        }

        s= "hit_point: times = " + to_string(root_1) + " " + to_string(root_2) + "\n";
    }
	else if(delta == 0) time = -B/(2*A);
    else return false;
    
    auto hit_point = ray(time);

    sf->primitive = primitive;
    sf->time = time;
    sf->wo = o - hit_point;
    sf->p = hit_point;
    sf->n = normalize_vector3f(hit_point - c);

    if (hit_point[1] >= 0.0) {
        // cout << s;
    }

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
