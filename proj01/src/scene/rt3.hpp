#ifndef RT3_HPP
#define RT3_HPP

#include <memory>

#include "camera.hpp"
#include "scene.hpp"

using std::unique_ptr;

struct Rt3{
	unique_ptr<Scene> scene;
	unique_ptr<Camera> camera;
	Rt3();
	Rt3(unique_ptr<Scene>, unique_ptr<Camera>);
};

#endif /* RT3_HPP */