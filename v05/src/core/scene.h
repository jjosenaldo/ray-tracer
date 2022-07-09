#ifndef SCENE_H
#define SCENE_H

#include <limits>
#include "background.h"
#include "primitive.h"
#include "ray.h"

class Scene {
    public:
        Primitive* aggregate;
        Background* background;
        Scene();
        bool intersect( const Ray& r, Surfel *isect, float min_t = 0.0, float max_t = std::numeric_limits<float>::max()/2 );
        bool intersect_p( const Ray& r );
};

#endif