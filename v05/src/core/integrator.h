#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "scene.h"

class Integrator {
    public:
        virtual ~Integrator() = default;
        virtual void render( Scene& scene ) =0;
};

#endif