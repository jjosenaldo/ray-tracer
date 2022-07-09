#include "scene.h"

Scene::Scene() {/* empty */ }

bool Scene::intersect( const Ray& r, Surfel *isect, float min_t, float max_t) {
    return aggregate->intersect(r, isect, min_t, max_t);
}

bool Scene::intersect_p( const Ray& r ) {
    return aggregate->intersect_p(r);
}