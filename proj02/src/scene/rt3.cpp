#include "rt3.hpp"

using std::move;

Rt3::Rt3(){

}

Rt3::Rt3(unique_ptr<Scene> scene, unique_ptr<Camera> camera){
	this->scene = move(scene);
	this->camera = move(camera);
}