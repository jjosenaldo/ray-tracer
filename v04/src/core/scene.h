#ifndef SCENE_H
#define SCENE_H

#include "background.h"
#include "primitive.h"
#include "ray.h"

class Scene {
    public:
        Primitive* aggregate;
        Background* background;
        Scene();
        bool intersect( const Ray& r, Surfel *isect );
        bool intersect_p( const Ray& r );
};

#endif