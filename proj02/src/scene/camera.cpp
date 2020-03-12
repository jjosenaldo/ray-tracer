#include "camera.hpp"

CameraType cameraTypeFromString(string str){
	if(str == "ortographic") return CameraType::CT_ORTHO;
	return CameraType::CT_ORTHO;
}

Camera::Camera(){
	
}

Camera::Camera(ParamSet ps){
	this->type = ps.find_one("type", CT_ORTHO);
}