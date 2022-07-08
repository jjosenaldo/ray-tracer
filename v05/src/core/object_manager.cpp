#include "object_manager.h"
#include "sphere.h"
#include "plane.h"

void ObjectManager::add_object(Primitive* obj) {
    obj_list.push_back(obj);
}

void ObjectManager::add_material(Material* _mat) {
     materials.push_back(_mat);
}

void ObjectManager::instantiate_sphere(const Point3f& _c, const float& _r, Material* mat) {
    Shape* shape = new Sphere(_c, _r);
    auto primitive = new GeometricPrimitive(shape, mat);
    shape->primitive = primitive;

    this->add_object(primitive);
}

void ObjectManager::instantiate_triangle(const Point3f& _p1, const Point3f& _p2, const Point3f& _p3, Material* mat) {
    Plane* plane = new Plane(mat, _p1, _p2, _p3);
    this->add_object(plane);
}

Material* ObjectManager::get_material(void) {
    return materials.back();
}

std::vector< Primitive* >& ObjectManager::get_object_list(void) {
	return obj_list;
}
