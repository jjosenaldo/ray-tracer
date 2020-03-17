#include "camera.hpp"

// TODO: remove this
#include <iostream>
using std::cout;
using std::endl;

CameraType cameraTypeFromString(string str){
	if(str == "ortographic") return CameraType::CT_ORTHO;
	if(str == "perspective") return CameraType::CT_PERSP;
	return CameraType::CT_ORTHO;
}

Camera::Camera(){
	l = r = b = t = -1;
}

void Camera::setFilm(unique_ptr<Film> film){
	// std::cout << "Camera::setFilm()_begin\n";
	this->film = move(film);

	// If the scren space wasn't defined, it should go from -1 to 1 in the lower dimension
	if(this->l < 0){
		if(this->film->width < this->film->height){
			this->l = -1;
			this->r = 1;
			float ratio = this->film->height /  (float)this->film->width;
			this->b = -ratio;
			this->t = ratio;
		} else{
			this->b = -1;
			this->t = 1;
			float ratio = this->film->width /  (float)this->film->height;
			this->l = -ratio;
			this->r = ratio;
		}
	}
	// std::cout << "Camera::setFilm()_end\n";
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
	bool lookFromDefined = false, lookAtDefined = false, upDefined = false;
	float* lookFrom = nullptr;
	float* lookAt = nullptr;
	float* up = nullptr;
	size_t dummyOutParam;

	for(auto& pair : ps.params){
		if(pair.first == "type")
			this->type = cameraTypeFromString(ps.findOneFromPsi<string>(pair.second));

		else if(pair.first == "lookAt" && !lookAtDefined){
			auto tmpLookAt = ps.findArrayFromPsi<float>(pair.second, dummyOutParam);
			lookAt = new float[3];
			for(int i = 0; i < 3; ++i) lookAt[i] = tmpLookAt[i];
			lookAtDefined = true;
		}
		else if(pair.first == "lookFrom" && !lookFromDefined){
			auto tmpLookFrom = ps.findArrayFromPsi<float>(pair.second, dummyOutParam);
			lookFrom = new float[3];
			for(int i = 0; i < 3; ++i) lookFrom[i] = tmpLookFrom[i];
			lookFromDefined = true;
		}
		else if(pair.first == "up" && !upDefined){
			auto tmpUp = ps.findArrayFromPsi<float>(pair.second, dummyOutParam);
			up = new float[3];
			for(int i = 0; i < 3; ++i) up[i] = tmpUp[i];
			upDefined = true;
		} else if(pair.first == "screenWindow"){
			auto screenWindow = ps.findArrayFromPsi<float>(pair.second, dummyOutParam);
			l = screenWindow[0];r = screenWindow[1];b = screenWindow[2];t = screenWindow[3];
		}
	}

	// TODO: what should happen if one or two of these guys aren't defined?
	if(lookAtDefined && lookFromDefined && upDefined){
		Vector3<float> gaze = Vector3<float>(lookAt[0],lookAt[1],lookAt[2]) - Vector3<float>(lookFrom[0],lookFrom[1],lookFrom[2]);
		this->w = gaze.normalize();
		this->u = crossProduct( Vector3<float>(up[0],up[1],up[2]), w ).normalize();
		this->v = crossProduct(w,u).normalize();
		this->e = Point3<float>(lookFrom[0],lookFrom[1],lookFrom[2]);	
		delete[] lookFrom;
		delete[] lookAt;
		delete[] up;
	}
	
}