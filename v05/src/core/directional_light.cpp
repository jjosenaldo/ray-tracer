#include "directional_light.h"

ColorXYZ DirectionalLight::sample_Li( const Surfel& hit, BlinnPhongMaterial& material, const Vector3f *wi, const VisibilityTester *vis) {
    auto L = normalize_vector3f(to - from);
    auto N = hit.n;
    auto V = hit.wo;
    auto H = normalize_vector3f(V+L);

    return sample_Li_from_nlh(N, L, H, material, wi, vis);
}

ColorXYZ DirectionalLight::get_I() {
    return I;
}