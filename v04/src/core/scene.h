#ifndef SCENE_H
#define SCENE_H

#include "background.h"
#include "ray.h"

class Scene {
    private:
        Primitive* aggregate;

    public:
        Background* background;
        Scene(Primitive* ag, Background* bkg ) : background{bkg}, aggregate{ag} {/* empty */ }
        bool intersect( const Ray& r, Surfel *isect ) const;
        bool intersect_p( const Ray& r ) const;
};

#endif