#include "linearalgebra.hpp"

float bilinearInterpolation(float x, float y, float bl, float tl, float tr, float br ){
	return bl*(1-x)*(1-y) + br*x*(1-y) + tl*(1-x)*y + tr*x*y;
}

Vector3<float> crossProduct(Vector3<float> a, Vector3<float> b){
	return Vector3<float>(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}