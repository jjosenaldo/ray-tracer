#ifndef NON_AMBIENT_LIGHT_H
#define NON_AMBIENT_LIGHT_H

#include "blinn_phong_material.h"
#include "light.h"
#include "visibility_tester.h"

class NonAmbientLight:  public Light {
    public:
        NonAmbientLight(ColorXYZ _scale): Light(_scale){}
        ColorXYZ sample_Li_from_nlh(Vector3f& n, Vector3f& l, Vector3f& h, BlinnPhongMaterial& material, Vector3f *wi, VisibilityTester *vis);
        virtual ColorXYZ I() = 0;
};

#endif