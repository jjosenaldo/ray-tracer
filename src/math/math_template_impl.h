#ifndef MATH_TEMPLATE_IMPL_H
#define MATH_TEMPLATE_IMPL_H

#include "math.h"

template <class T>
function<T(Point2)> bilinear_interpolation(Point2 tl, Point2 bl, Point2 br, Point2 tr, T val_tl, T val_bl, T val_br, T val_tr)
{
    return [=](Point2 p)
    {
        return (val_bl * (tr.x - p.x) * (tr.y - p.y) + val_br * (p.x - bl.x) * (tr.y - p.y) + val_tl * (br.x - p.x) * (p.y - br.y) + val_tr * (p.x - bl.x) * (p.y - br.y)) / ((br.x - bl.x) * (tr.y - br.y));
    };
}

#endif