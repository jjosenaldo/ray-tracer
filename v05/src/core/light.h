#ifndef LIGHT_H
#define LIGHT_H

#include "scene.h"
#include "surfel.h"
#include "visibility_tester.h"
#include "blinn_phong_material.h"

class Light {
public:
    ColorXYZ scale;
    Light(ColorXYZ _scale): scale(_scale){};
    // Retorna a intensidade da luz, direção e o teste oclusão.
    virtual ColorXYZ sample_Li( const Surfel& hit, BlinnPhongMaterial& material, const Vector3f *wi, const VisibilityTester *vis) = 0;
    virtual void preprocess( const Scene & ) {};
    virtual Point3f max_shadow_ray_point(Point3f origin) = 0;
};

#endif