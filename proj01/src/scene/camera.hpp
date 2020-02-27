#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "paramset.hpp"

enum CameraType{
	CT_ORTHO
};

struct Camera{
	CameraType type;
	Camera();
	Camera(ParamSet ps);
};

#endif