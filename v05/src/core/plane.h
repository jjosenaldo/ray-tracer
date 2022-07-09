#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"
#include "shape.h"
#include "material.h"

class Plane : public Primitive {
    private:
        Material* material;
        Point3f p1;
        Point3f p2;
        Point3f p3;
        Vector3f n;

    public:
        Plane(Material* m, const Point3f& _p1, const Point3f& _p2, const Point3f& _p3);
        ~Plane(){}
        bool intersect( const Ray& r, Surfel *sf, float min_t, float max_t ) override;
        // Simpler and faster version of intersection that only return true/false.
        // It does not compute the hit point information.
        bool intersect_p( const Ray& r) override;
        //virtual Bounds3f world_bounds() const = 0;
        Material* get_material() ;
        void set_material(Material*& mat);
 };

 // Given a line defined by p1 and p2, returns whether p is on the same side as p3
 bool same_side_as(Point3f p1, Point3f p2, Point3f p3, Point3f p);

#endif