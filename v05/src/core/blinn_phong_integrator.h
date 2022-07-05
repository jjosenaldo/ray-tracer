#ifndef BLINN_PHONG_INTEGRATOR_H
#define BLINN_PHONG_INTEGRATOR_H

#include "sampler_integrator.h"

class BlinnPhongIntegrator: public SamplerIntegrator {
    public:
        using SamplerIntegrator::Li;
        BlinnPhongIntegrator(Camera* camera);
        ColorXYZ Li( const Ray& ray, Scene& scene, ColorXYZ& default_color);
        ColorXYZ Li( const Ray& ray, Scene& scene, ColorXYZ& default_color, int depth);
};


#endif