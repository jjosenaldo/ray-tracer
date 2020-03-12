#include "camera.hpp"

// TODO: remove this
#include <iostream>
using std::cout;

CameraType cameraTypeFromString(string str){
	if(str == "ortographic") return CameraType::CT_ORTHO;
	return CameraType::CT_ORTHO;
}

Camera::Camera(){
	
}

// TODO
Ray Camera::generateRay(int x, int y){
	return Ray();
}

// TODO
Ray Camera::generateRay(float x, float y){
	return Ray();
}

void Camera::readParamSet(ParamSet ps){
	for(auto& pair : ps.params){
		if(pair.first == "type")
			this->type = ps.find_one("type", CT_ORTHO);
		else if(pair.first == "lookAt")
			cout << "lookAtDefined;\n";
		else if(pair.first == "lookFrom")
			cout << "lookFromDefined;\n";
		else if(pair.first == "up")
			cout << "upDefined;\n";

	}


}