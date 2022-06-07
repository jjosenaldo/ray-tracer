#ifndef FLAT_INTEGRATOR_H
#define FLAT_INTEGRATOR_H

#include "sampler_integrator.h"

class FlatIntegrator: public SamplerIntegrator {
    public:
        using SamplerIntegrator::Li;
        ColorXYZ Li( const Ray& ray, const Scene& scene, ColorXYZ& default_color);
};


#endif