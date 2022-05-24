#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <functional>
#include "vec3.h"

using std::function;

class Background {
    private:
        function<ColorXYZ(Point2f)> sampler;

    public:
        Background(){}
        Background(ColorXYZ color);
        Background(ColorXYZ bl, ColorXYZ tl, ColorXYZ tr, ColorXYZ br);
	virtual ~Background() = default;
        ColorXYZ sample(Point2f);
};
#endif
