#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "geometric_primitive.h"

class ObjectManager {
    private:
        std::vector< Material* > materials;
        std::vector< Primitive* > obj_list;

    public:
        ObjectManager(){}
        ~ObjectManager(){}

        void add_object(Primitive* obj);
        void add_material(Material* _mat);
        void instantiate_sphere(const Point3f& _c, const float& _r, Material* mat);
        void instantiate_triangle(const Point3f& _p1, const Point3f& _p2, const Point3f& _p3, Material* mat);
        Material* get_material(void);
	    std::vector< Primitive* >& get_object_list(void);
};

#endif
