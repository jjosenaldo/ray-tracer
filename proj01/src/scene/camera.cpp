#include "camera.hpp"

Camera::Camera(){
	
}

Camera::Camera(ParamSet ps){
	this->type = ps.find_one("type", CT_ORTHO);
}