#ifndef RAY_HPP
#define RAY_HPP

#include "linearalgebra.hpp"

struct Ray{
	Point3<int> origin;
	Vector3<int> direction;

	Ray();
	Ray(Point3<int> origin, Vector3<int> direction);
};

#endif /* RAY_HPP */