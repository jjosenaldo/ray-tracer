#include "scene.h"

Scene::Scene() {/* empty */ }

bool Scene::intersect( const Ray& r, Surfel *isect ) {
    return aggregate->intersect(r, isect);
}

bool Scene::intersect_p( const Ray& r ) {
    return aggregate->intersect_p(r);
}