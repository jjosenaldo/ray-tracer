#include "directional_light.h"

ColorXYZ DirectionalLight::sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis) {
    Vector3f direction = to - from;
    Vector3f norm_direction = normalize_vector3f(direction);
    Vector3f N = hit.n;
    Vector3f V = hit.wo;
    Vector3f H = normalize_vector3f(V+norm_direction);

    Surfel light = Surfel(hit.p - norm_direction, N, norm_direction, norm_vector3f(direction));

    vis = new VisibilityTester(hit, light);
    //wi = norm_direction;

    return sample_Li_from_nlh(N, norm_direction, H, material, wi, vis);
}

ColorXYZ DirectionalLight::get_I() {
    return I;
}

Ray DirectionalLight::shadow_ray(Point3f origin) {
    auto direction = to - from;

    return Ray(origin, direction);
}