#ifndef MATH_TEMPLATE_IMPL_H
#define MATH_TEMPLATE_IMPL_H

#include "math.h"

template <class T>
function<T(Point2f)> bilinear_interpolation(Point2f tl, Point2f bl, Point2f br, Point2f tr, T val_tl, T val_bl, T val_br, T val_tr)
{
    return [=](Point2f p)
    {
        return (val_bl * (tr[0] - p[0]) * (tl[1] - p[1]) + val_br * (p[0] - bl[0]) * (tr[1] - p[1]) + val_tl * (br[0] - p[0]) * (p[1] - br[1]) + val_tr * (p[0] - bl[0]) * (p[1] - br[1])) / ((br[0] - bl[0]) * (tr[1] - br[1]));
    };
}

#endif
