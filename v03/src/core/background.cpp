#include "background.h"
#include "math.h"
#include <iostream>

Background::Background(ColorXYZ color) {
    sampler = bilinear_interpolation<ColorXYZ>({0, 1}, {0, 0}, {1, 0}, {1, 1}, color, color, color, color);
}

Background::Background(ColorXYZ bl, ColorXYZ tl, ColorXYZ tr, ColorXYZ br) {
    sampler = bilinear_interpolation<ColorXYZ>({0, 1}, {0, 0}, {1, 0}, {1, 1}, tl, bl, br, tr);
}

ColorXYZ Background::sample(Point2f point) {
    return sampler(point);
}
