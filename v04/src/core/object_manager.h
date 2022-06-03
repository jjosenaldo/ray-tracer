#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "geometric_primitive.h"

class ObjectManager {
    private:
        Material* mat;
        std::vector< Primitive* > obj_list;

    public:
        ObjectManager(){}
        ~ObjectManager(){}

        void add_object(Primitive* obj);
        void add_material(Material* _mat);
        void instantiate_sphere(const Point3f& _c, const float& _r, Material* mat);
        Material* get_material(void);
	    std::vector< Primitive* >& get_object_list(void);
};

#endif
