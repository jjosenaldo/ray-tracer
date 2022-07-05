#include <algorithm>
#include <cmath>
#include "non_ambient_light.h"

using std::max;

ColorXYZ NonAmbientLight::sample_Li_from_nlh(Vector3f& n, Vector3f& l, Vector3f& h, BlinnPhongMaterial& material, Vector3f *wi, VisibilityTester *vis) {
    auto dot_nl = max(0.0f, dot_vector3f(n, l));
    auto dot_nh = pow(max(0.0f, dot_vector3f(n, h)), material.g);

    return material.kd * I() * dot_nl + material.ks * I() * dot_nh;
}