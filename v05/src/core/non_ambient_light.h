#ifndef NON_AMBIENT_LIGHT_H
#define NON_AMBIENT_LIGHT_H

#include "blinn_phong_material.h"
#include "light.h"
#include "visibility_tester.h"

class NonAmbientLight:  public Light {
    public:
        NonAmbientLight(ColorXYZ _scale): Light(_scale){}
        ColorXYZ sample_Li_from_nlh(Vector3f& n, Vector3f& l, Vector3f& h, BlinnPhongMaterial& material, const Vector3f* wi, const VisibilityTester* vis);
        virtual ColorXYZ get_I() = 0;
};

#endif