#include "spot_light.h"

ColorXYZ SpotLight::sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis) {
    Vector3f direction = from - hit.p;
    Vector3f norm_direction = normalize_vector3f(direction);
    Vector3f N = hit.n;
    Vector3f V = hit.wo;
    Vector3f H = normalize_vector3f((V)+norm_direction);

    Surfel* light = new Surfel(from, N, norm_direction, norm_vector3f(direction));
    auto new_vis = new VisibilityTester(hit, *light);
    //vis->copy_from(new_vis);
    wi = &norm_direction;

    return sample_Li_from_nlh(N, norm_direction, H, material, wi, vis);
}

ColorXYZ SpotLight::get_I() {
    return I;
}

Ray SpotLight::shadow_ray(Point3f origin) {
    Vector3f direction = from - origin;

    return Ray(origin, direction);
}