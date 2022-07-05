#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "light.h"
#include "non_ambient_light.h"

class DirectionalLight:  public NonAmbientLight {
    public:
        ColorXYZ I;
        Vector3f from;
        Vector3f to;
        DirectionalLight(ColorXYZ _I, Vector3f _from, Vector3f _to, ColorXYZ _scale): I(_I), from(_from), to(_to), NonAmbientLight(_scale){}
};

#endif