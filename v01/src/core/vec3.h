
#ifndef VEC3_H
#define VEC3_H

#include <stdexcept>
#include <vector> //Try later using own vector instead
#include <array>

using Vector3f = std::array<float, 3>;
using ColorXYZ = std::array<float, 3>;
using Spectrum = std::array<float, 3>;
using Normal3f = std::array<float, 3>;
using Ray = std::array<float, 3>;
using Point3f = std::array<float, 3>;
using Vector3i = std::array<int, 3>;
using Point2f = std::array<float, 2>;
using Point2i = std::array<int, 2>;

ColorXYZ default_colorxyz();
bool is_colorxyz_default(ColorXYZ color);

ColorXYZ operator*(const ColorXYZ& color, const float& val);

ColorXYZ operator/(const ColorXYZ& color, const float& val);

ColorXYZ operator+(const ColorXYZ& color, const float& val);

ColorXYZ operator+(const ColorXYZ& color1, const ColorXYZ& color2);

#endif // VEC3_H
