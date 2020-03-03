#ifndef LINEARALGEBRA_HPP
#define LINEARALGEBRA_HPP

template <typename T> 
struct Point2{
    T x;
    T y;
};

float bilinearInterpolation(float x, float y, float bl, float tl, float tr, float br );

#endif /* LINEARALGEBRA_HPP */