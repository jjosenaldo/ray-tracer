#include "visibility_tester.h"
#include <iostream>

VisibilityTester::VisibilityTester(const Surfel& obj, const Surfel& light) {
    std::cout << "Entered VisibilityTester\n";
    objectContact->copy_from(&obj);
    lightContact->copy_from(&light);
    std::cout << "Got out VisibilityTester\n";
}

bool VisibilityTester::unoccluded(Scene& scene) {
    Ray lightRay = Ray(lightContact->p, lightContact->wo);
    return !scene.intersect_p(lightRay);
}


void VisibilityTester::copy_from(const VisibilityTester* other) {
    if (!other) return;

    objectContact->copy_from(other->objectContact);
    lightContact->copy_from(other->lightContact);
}