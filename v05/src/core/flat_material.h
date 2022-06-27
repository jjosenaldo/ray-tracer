#ifndef FLAT_MATERIAL_H
#define FLAT_MATERIAL_H

#include "material.h"
#include "vec3.h"

class FlatMaterial: public Material {
    private:
        ColorXYZ color;

    public:
        FlatMaterial(const ColorXYZ _color) : color{_color} {/* empty */ }
        ~FlatMaterial(){}
        ColorXYZ kd();
};

#endif