#include "object_manager.h"
#include "sphere.h"

void ObjectManager::add_object(Primitive* obj) {
    obj_list.push_back(obj);
}

void ObjectManager::add_material(Material* _mat) {
     mat = _mat;
}

void ObjectManager::instantiate_sphere(const Point3f& _c, const float& _r, Material* mat) {
    Primitive* sp = new Sphere(_c, _r, mat);
    add_object(sp);
}

Material* ObjectManager::get_material(void) {
    return mat;
}

std::vector< Primitive* >& ObjectManager::get_object_list(void) {
	return obj_list;
}
