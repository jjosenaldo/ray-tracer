#include "ray.hpp"

Ray::Ray() : Ray(Point3<int>(), Vector3<int>()) {}

Ray::Ray(Point3<int> origin, Vector3<int> direction){
	this->origin = origin;
	this->direction = direction;
}