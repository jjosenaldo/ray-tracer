#include "point_light.h"

using namespace std;

ColorXYZ PointLight::sample_Li( const Surfel& hit, BlinnPhongMaterial& material, const Vector3f *wi, const VisibilityTester *vis) {
    auto L = normalize_vector3f(from - hit.p);
    auto N = hit.n;
    auto V = hit.wo;
    auto H = normalize_vector3f(V+L);

    return sample_Li_from_nlh(N, L, H, material, wi, vis);
}

ColorXYZ PointLight::get_I() {
    return I;
}

Point3f PointLight::max_shadow_ray_point(Point3f origin) {
    return from;
}