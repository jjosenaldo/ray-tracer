#ifndef LIGHT_H
#define LIGHT_H

#include "ray.h"
#include "scene.h"
#include "surfel.h"
#include "visibility_tester.h"
#include "blinn_phong_material.h"

class Light {
public:
    ColorXYZ scale;
    Light(ColorXYZ _scale): scale(_scale){};
    // Retorna a intensidade da luz, direção e o teste oclusão.
    virtual ColorXYZ sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis) = 0;
    virtual void preprocess( const Scene & ) {};
    virtual Ray shadow_ray(Point3f origin) = 0;
};

#endif