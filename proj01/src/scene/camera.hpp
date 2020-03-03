#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "film.hpp"
#include "paramset.hpp"

enum CameraType{
	CT_ORTHO
};

CameraType cameraTypeFromString(string str);

struct Camera{
	CameraType type;
	unique_ptr<Film> film;
	Camera();
	Camera(ParamSet ps);
};

#endif