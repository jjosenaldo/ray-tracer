#include <limits>
#include "vec3.h"

using std::numeric_limits;

ColorXYZ default_colorxyz() {
    return {-1.0, -1.0, -1.0};
}

bool is_colorxyz_default(ColorXYZ color) {
    for (float component: color) {
        if (component < 0) {
            return true;
        }
    }

    return false;
}

Point4f default_point4f() {
  return {numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min()};
}

bool is_point4f_default(Point4f& point) {
  for (unsigned int i = 0; i < 4; ++i) {
    if (point[i] != numeric_limits<float>::min()) return false;
  }
  return true;
}

Point3f default_point3f() {
  return {numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min()};
}

bool is_point3f_default(Point3f& point) {
  for (unsigned int i = 0; i < 3; ++i) {
    if (point[i] != numeric_limits<float>::min()) return false;
  }
  return true;
}

Vector3f default_vector3f() {
  return default_point3f();
}

bool is_vector3f_default(Vector3f& vector) {
  return is_point3f_default(vector);
}

ColorXYZ operator*(const ColorXYZ& color, const float& val) {
  return {color[0]*val, color[1]*val, color[2]*val};
}

ColorXYZ operator/(const ColorXYZ& color, const float& val) {
  return {color[0]/val, color[1]/val, color[2]/val};
}

ColorXYZ operator+(const ColorXYZ& color, const float& val) {
  return {color[0]+val, color[1]+val, color[2]+val};
}

ColorXYZ operator+(const ColorXYZ& color1, const ColorXYZ& color2) {
  return {color1[0]+color2[0], color1[1]+color2[1], color1[2]+color2[2]};
}

Vector3f operator*(const float& scalar, const Vector3f& vector)  {
  return {vector[0]*scalar, vector[1]*scalar, vector[2]*scalar};
}