#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "blinn_phong_material.h"
#include "light.h"
#include "non_ambient_light.h"
#include "visibility_tester.h"

class PointLight:  public NonAmbientLight {
    private:
        ColorXYZ I;
    public:
        Point3f from;
        PointLight(ColorXYZ _I, Point3f _from, ColorXYZ _scale): NonAmbientLight(_scale), I(_I), from(_from) {}
        ColorXYZ sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis);
        ColorXYZ get_I();
        Point3f max_shadow_ray_point(Point3f origin);
};

#endif