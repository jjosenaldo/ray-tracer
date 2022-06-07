#ifndef SCENE_H
#define SCENE_H

#include "background.h"
#include "primitive.h"
#include "ray.h"

class Scene {
    private:
        Primitive* aggregate;

    public:
        Background* background;
        Scene(Primitive* ag, Background* bkg);
        bool intersect( const Ray& r, Surfel *isect );
        bool intersect_p( const Ray& r );
};

#endif