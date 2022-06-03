#ifndef GEOMETRIC_PRIMITIVE_H
#define GEOMETRIC_PRIMITIVE_H

#include "primitive.h"
#include "shape.h"
#include "material.h"

class GeometricPrimitive : public Primitive {
    private:
        Shape* shape;
        Material* material;

    public:
        GeometricPrimitive(Shape* s, Material* m) : shape{s}, material{m}{}
        ~GeometricPrimitive(){}
        bool intersect( const Ray& r, const Surfel *sf ) const override;
        // Simpler and faster version of intersection that only return true/false.
        // It does not compute the hit point information.
        bool intersect_p( const Ray& r) const override;
        //virtual Bounds3f world_bounds() const = 0;
        Material* get_material(void) const;
        void set_material(Material*& mat);
 };

#endif