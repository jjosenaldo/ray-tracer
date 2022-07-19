#include "point_light.h"

using namespace std;

ColorXYZ PointLight::sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis) {
    // pelo pdf deveria ser hit.p - from
    Vector3f direction = from - hit.p;
    Vector3f norm_direction = normalize_vector3f(direction);
    Vector3f N = hit.n;
    Vector3f V = hit.wo;
    Vector3f H = normalize_vector3f(V+norm_direction);

    Surfel* light = new Surfel(from, N, norm_direction, norm_vector3f(direction));
    auto new_vis = new VisibilityTester(hit, *light);
    //vis->copy_from(new_vis);
    wi = &norm_direction;

    return sample_Li_from_nlh(N, norm_direction, H, material, wi, vis);
}

ColorXYZ PointLight::get_I() {
    return I;
}

Point3f PointLight::max_shadow_ray_point(Point3f origin) {
    return from;
}