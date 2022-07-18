#include "visibility_tester.h"

VisibilityTester::VisibilityTester(Surfel& obj, Surfel& light) {
    objectContact->copy_from(&obj);
    lightContact->copy_from(&light);
}

bool VisibilityTester::unoccluded(Scene& scene) {
    Ray lightRay = Ray(lightContact->p, lightContact->wo);
    return !scene.intersect_p(lightRay);
}