#ifndef LINEARALGEBRA_HPP
#define LINEARALGEBRA_HPP

#include <cmath> // sqrt()
#include <string>

using std::string;
using std::to_string;

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
    Point3 operator-(const Point3& other){
        return Point3(other.x-x,other.y-y,other.z-z);
    }
    Point3 normalize(){
        float norm = sqrt(x*x+y*y+z*z);
        return Point3(x/norm,y/norm,z/norm);
    }
    string toString(){
        return "<"+to_string(x)+","+to_string(y)+","+to_string(z)+">";
    }
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

template <typename T>
using Vector3 = Point3<T>;


float bilinearInterpolation(float x, float y, float bl, float tl, float tr, float br );

Vector3<float> crossProduct(Vector3<float> v1, Vector3<float> v2);

#endif /* LINEARALGEBRA_HPP */