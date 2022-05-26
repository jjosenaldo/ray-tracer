#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
    private:

    public:
        ColorXYZ color;

        Material(const ColorXYZ _color) : color{_color} {/* empty */ }
        ~Material(){}
};

#endif