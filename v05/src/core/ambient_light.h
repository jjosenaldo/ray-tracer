#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "light.h"

class AmbientLight:  public Light {
    public:
        ColorXYZ L;
        AmbientLight(ColorXYZ _L, ColorXYZ _scale): L(_L), Light(_scale){}
};

#endif