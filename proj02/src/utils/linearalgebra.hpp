#ifndef LINEARALGEBRA_HPP
#define LINEARALGEBRA_HPP

#include <cmath> // sqrt()
#include <ostream>
#include <string>

using std::ostream;
using std::string;
using std::to_string;

template <typename T> 
struct Point2{
    T x;
    T y;
    Point2(T x, T y){this->x=x;this->y=y;}
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
    float norm(){
        return sqrt(x*x+y*y+z*z);
    }
    Point3 normalize(){
        float n = norm();
        return Point3(x/n,y/n,z/n);
    }
    string toString(){
        return "<"+to_string(x)+","+to_string(y)+","+to_string(z)+">";
    }
    friend ostream& operator<<(ostream& os, Point3 const & p) {
        return os << "(" << p.x << "," << p.y << "," << p.z <<  ")";
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

template <typename T>
struct Ray{
    Vector3<T> direction;
    Point3<T> origin;
    Vector3<T> u, v, w;
    Ray<T>(Vector3<T> direction, Point3<T> origin, Vector3<T> u, Vector3<T> v, Vector3<T> w){
        this->direction=direction;this->origin=origin;this->u=u;this->v=v;this->w=w;
    }
    friend ostream& operator<<(ostream& os, Ray const & ray) {
        return os << "{" << ray.direction << "," << ray.origin << "}";
    }
};

float bilinearInterpolation(float x, float y, float bl, float tl, float tr, float br );

Vector3<float> crossProduct(Vector3<float> v1, Vector3<float> v2);

#endif /* LINEARALGEBRA_HPP */