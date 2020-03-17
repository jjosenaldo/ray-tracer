#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>
#include <vector>

#include "film.hpp"
#include "linearalgebra.hpp"
#include "paramset.hpp"

using std::vector;

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
	Point2<float> screenSpaceCoordinateFromPixel(int row, int col);

	// TODO: this method should be purely abstract
	virtual Ray<float> generateRay(int row, int col);

	/* The first ParamSet in the vector must contain the camera type! */
	static unique_ptr<Camera> makeCamera(vector<ParamSet>& paramSets);

};

struct PerspectiveCamera : Camera{
	Ray<float> generateRay(int row, int col);
};

// TODO: generateRay
struct OrtographicCamera : Camera{

};

#endif