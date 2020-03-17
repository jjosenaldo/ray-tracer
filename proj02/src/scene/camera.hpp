#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "film.hpp"
#include "paramset.hpp"
#include "ray.hpp"

enum CameraType{
	CT_ORTHO,
	CT_PERSP
};

CameraType cameraTypeFromString(string str);

struct Camera{
	CameraType type;
	unique_ptr<Film> film;
	Vector3<float> u,v,w;
	Point3<float> e;
	float l, r, b, t;

	Camera();
	void readParamSet(ParamSet ps);

	void setFilm(unique_ptr<Film> film);

	// TODO: these should be purely abstract methods
	virtual Ray generateRay(int x, int y);
	virtual Ray generateRay(float x, float y);

};

struct PerspectiveCamera : Camera{

};

struct OrtographicCamera : Camera{

};

#endif