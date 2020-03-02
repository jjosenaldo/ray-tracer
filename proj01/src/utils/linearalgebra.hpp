#ifndef LINEARALGEBRA_HPP
#define LINEARALGEBRA_HPP

struct Point2{
    int x;
    int y;
};

float bilinearInterpolation(float x, float y, float bl, float tl, float tr, float br );

#endif /* LINEARALGEBRA_HPP */