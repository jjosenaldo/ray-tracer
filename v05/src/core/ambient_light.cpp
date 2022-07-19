#include "ambient_light.h"

ColorXYZ AmbientLight::sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis) {
    return get_I() * material.ka;
}

ColorXYZ AmbientLight::get_I() {
    return I;
}

Ray AmbientLight::shadow_ray(Point3f origin) {
    return Ray(origin, origin);
}