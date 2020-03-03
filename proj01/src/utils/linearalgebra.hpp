#ifndef LINEARALGEBRA_HPP
#define LINEARALGEBRA_HPP

template <typename T> 
struct Point2{
    T x;
    T y;
};

template <typename T> 
struct Point3{
    T x;
    T y;
    T z;
    Point3<T>() : Point3<T>(0,0,0){}
    Point3<T>(T x, T y, T z){set(x,y,z); }
    void set(T x, T y, T z){this->x=x;this->y=y;this->z=z;}
};

template <typename T>
struct RgbColor : public Point3<T> {
	T r(){return this->x;}
	T g(){return this->y;}
	T b(){return this->z;}
	RgbColor<T>() : Point3<T>(){}
	RgbColor<T>(T r, T g, T b) : Point3<T>(r,g,b){}
};

typedef RgbColor<unsigned char> RgbColorChar;


float bilinearInterpolation(float x, float y, float bl, float tl, float tr, float br );

#endif /* LINEARALGEBRA_HPP */