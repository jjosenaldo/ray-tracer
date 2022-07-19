#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "light.h"

class AmbientLight : public Light {
    private:
        ColorXYZ I;
    public:
        float flux;
        AmbientLight(ColorXYZ _I, ColorXYZ _scale, float _flux): I(_I), flux(_flux), Light(_scale){}

        ColorXYZ sample_Li( const Surfel& hit, BlinnPhongMaterial& material, Vector3f* wi, VisibilityTester* vis);
        ColorXYZ get_I();
        Ray shadow_ray(Point3f origin);
};

#endif