#include <algorithm>
#include <cmath>
#include "non_ambient_light.h"

using std::max;

#include <iostream>
using namespace std;

ColorXYZ NonAmbientLight::sample_Li_from_nlh(Vector3f& n, Vector3f& l, Vector3f& h, BlinnPhongMaterial& material, const Vector3f *wi, const VisibilityTester *vis) {
    auto dot_nl = max(0.0f, dot_vector3f(n, l));
    auto dot_nh = pow(max(0.0f, dot_vector3f(n, h)), material.g);
    auto diffuse = material.kd * get_I() * dot_nl;
    auto specular = material.ks * get_I() * dot_nh;

    if (material.ks[0] == 0.0) {
        cout << "diffuse=(" << diffuse[0] << " " << diffuse[1] << " " << diffuse[2] << "), specular=("
        << specular[0] << " " << specular[1] << " " << specular[2] << ")\n";
        cout << "dot_nl=" << dot_nl << endl;
        cout << "n=" << n[0] << " " << n[1] << " " << n[2] << endl;
        cout << "l=" << l[0] << " " << l[1] << " " << l[2] << endl;
    }

    return specular + diffuse;
}