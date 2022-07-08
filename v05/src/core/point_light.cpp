#include "point_light.h"

#include <iostream>
using namespace std;

ColorXYZ PointLight::sample_Li( const Surfel& hit, BlinnPhongMaterial& material, const Vector3f *wi, const VisibilityTester *vis) {
    auto L = normalize_vector3f(hit.p - from);
    auto N = hit.n;
    auto V = hit.wo;
    auto H = normalize_vector3f(V+L);

    if (material.ks[0] == 0.0) {
        cout << "Calculating color of point (" << hit.p[0] << " " << hit.p[1] << " " << hit.p[2] << "): ";
    }

    return sample_Li_from_nlh(N, L, H, material, wi, vis);
}

ColorXYZ PointLight::get_I() {
    return I;
}