#ifndef MATH_H
#define MATH_H

#include <functional>
#include <iostream>

using std::function;
using std::ostream;

struct Point2
{
    int x;
    int y;

    friend ostream &operator<<(ostream &os, const Point2 &pixel);
};

template <class T>
function<T(Point2)> bilinear_interpolation(Point2 tl, Point2 bl, Point2 br, Point2 tr, T val_tl, T val_bl, T val_br, T val_tr);

#include "math_template_impl.h"

#endif