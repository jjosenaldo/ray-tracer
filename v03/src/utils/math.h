#ifndef MATH_H
#define MATH_H

#include <functional>
#include <iostream>
#include "vec3.h"

using std::function;
using std::ostream;

template <class T>
function<T(Point2f)> bilinear_interpolation(Point2f tl, Point2f bl, Point2f br, Point2f tr, T val_tl, T val_bl, T val_br, T val_tr);

ostream &operator<<(ostream &os, const Point2f &point);

#include "math_template_impl.h"

#endif
