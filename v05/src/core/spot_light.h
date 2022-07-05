#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "light.h"
#include "non_ambient_light.h"

class SpotLight:  public NonAmbientLight {
    public:
        ColorXYZ I;
        Point3f from;
        Point3f to;
        int cutoff;
        int falloff;
        SpotLight(ColorXYZ _I, Point3f _from, Point3f _to, int _cutoff, int _falloff, ColorXYZ _scale): I(_I), from(_from), to(_to), cutoff(_cutoff), falloff(_falloff), NonAmbientLight(_scale){}
};

#endif