#include "linearalgebra.hpp"

float bilinearInterpolation(float x, float y, float bl, float tl, float tr, float br ){
	return bl*(1-x)*(1-y) + br*x*(1-y) + tl*(1-x)*y + tr*x*y;
}