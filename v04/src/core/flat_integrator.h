#ifndef FLAT_INTEGRATOR_H
#define FLAT_INTEGRATOR_H

#include "sampler_integrator.h"

class FlatIntegrator: public SamplerIntegrator {
    public:
        using SamplerIntegrator::Li;
        FlatIntegrator(Camera* camera);
        ColorXYZ Li( const Ray& ray, Scene& scene, ColorXYZ& default_color);
};


#endif