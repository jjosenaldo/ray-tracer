#ifndef SAMPLER_INTEGRATOR_H
#define SAMPLER_INTEGRATOR_H

#include "camera.h"
#include "integrator.h"
#include "rt3.h"
#include "vec3.h"

class SamplerIntegrator : public Integrator {
    public:
        virtual ~SamplerIntegrator();
        SamplerIntegrator( Camera* cam ) : camera{cam} { };

        // returns the incident radiance at the origin of a given ray
        virtual ColorXYZ Li( const Ray& ray, const Scene& scene, ColorXYZ& default_color) const = 0;
        virtual void render( const Scene& scene );
        virtual void preprocess( const Scene& scene );
        
    protected:
        Camera* camera;
        RunningOptions run_opt;
};

#endif