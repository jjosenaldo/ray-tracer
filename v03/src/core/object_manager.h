#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "primitive.h"

class ObjectManager {
    private:
        std::vector< Primitive* > obj_list;
        Material* mat;

    public:
        ObjectManager(){}
        ~ObjectManager(){}

        void add_object(Primitive* obj);
        void add_material(Material* _mat);
        void instantiate_sphere(const Point3f& _c, const float& _r, Material* mat);
        Material* get_material(void);
};

#endif