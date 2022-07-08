
#ifndef VEC3_H
#define VEC3_H

#include <stdexcept>
#include <vector> //Try later using own vector instead
#include <array>

using Vector3f = std::array<float, 3>;
using ColorXYZ = std::array<float, 3>;
using Spectrum = std::array<float, 3>;
using Normal3f = std::array<float, 3>;
using Point3f = std::array<float, 3>;
using Vector3i = std::array<int, 3>;
using Point4f = std::array<float, 4>;
using Point3f = std::array<float, 3>;
using Point2f = std::array<float, 2>;
using Point2i = std::array<int, 2>;

ColorXYZ default_colorxyz();
bool is_colorxyz_default(ColorXYZ color);

Point4f default_point4f();
bool is_point4f_default(Point4f& point);

Point3f default_point3f();
bool is_point3f_default(Point3f& point);

Vector3f default_vector3f();
bool is_vector3f_default(Vector3f& vector);

Vector3f normalize_vector3f(const Vector3f& vector);

Vector3f cross_vector3f(const Vector3f& vector1, const Vector3f& vector2);

float dot_vector3f(const Vector3f& vector1, const Vector3f& vector2);

Vector3f proj_vector3f(const Vector3f& vector_a, const Vector3f& vector_b);

float norm_vector3f(const Vector3f& v);

Vector3f operator-(const Vector3f& vector1, const Vector3f& vector2);

ColorXYZ operator*(const ColorXYZ& color, const float& val);

ColorXYZ operator*(const ColorXYZ& color1, const ColorXYZ& color2);

ColorXYZ operator/(const ColorXYZ& color, const float& val);

ColorXYZ operator+(const ColorXYZ& color, const float& val);

ColorXYZ operator+(const ColorXYZ& color1, const ColorXYZ& color2);

Vector3f operator*(const float& scalar, const Vector3f& vector);

// gambiarra
// TODO solucao sem gambiarra
class Primitive;
class Surfel;

#endif // VEC3_H
