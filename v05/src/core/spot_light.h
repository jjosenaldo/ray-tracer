#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "non_ambient_light.h"

class SpotLight : public NonAmbientLight {
    private:
        ColorXYZ I;

    public:
        Point3f from;
        Point3f to;
        int cutoff;
        int falloff;
        SpotLight(ColorXYZ _I, Point3f _from, Point3f _to, ColorXYZ _scale, int _cutoff, int _falloff): I(_I), from(_from), to(_to), cutoff(_cutoff), falloff(_falloff), NonAmbientLight(_scale){}

        ColorXYZ sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis);
        ColorXYZ get_I();
        Ray shadow_ray(Point3f origin);
};

#endif