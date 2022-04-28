#include "vec3.h"

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