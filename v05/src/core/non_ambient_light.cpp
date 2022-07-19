#include <algorithm>
#include <cmath>
#include "non_ambient_light.h"

using std::max;

ColorXYZ NonAmbientLight::sample_Li_from_nlh(Vector3f& n, Vector3f& l, Vector3f& h, BlinnPhongMaterial& material, const Vector3f* wi, const VisibilityTester* vis) {
    auto dot_nl = max(0.0f, dot_vector3f(n, l));
    auto dot_nh = pow(max(0.0f, dot_vector3f(n, h)), material.g);
    auto diffuse = material.kd * get_I() * dot_nl;
    auto specular = material.ks * get_I() * dot_nh;

    return specular + diffuse;
}