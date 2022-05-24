#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include "primitive.h"

class ObjectManager {
    private:
        
        Material* mat;

    public:
        ObjectManager(){}
        ~ObjectManager(){}

        std::vector< Primitive* > obj_list;
        void add_object(Primitive* obj);
        void add_material(Material* _mat);
        void instantiate_sphere(const Point3f& _c, const float& _r, Material* mat);
        Material* get_material(void);
};

#endif