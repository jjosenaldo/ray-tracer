#ifndef BLINN_PHONG_INTEGRATOR_H
#define BLINN_PHONG_INTEGRATOR_H

#include <vector>
#include "light.h"
#include "sampler_integrator.h"

using std::vector;

class BlinnPhongIntegrator: public SamplerIntegrator {
    private:
        vector<Light*> lights;
        int depth;
    public:
        using SamplerIntegrator::Li;
        BlinnPhongIntegrator(Camera* camera, int depth);
        void set_lights(vector<Light*> lights);
        ColorXYZ Li( const Ray& ray, Scene& scene, ColorXYZ& default_color);
        ColorXYZ Li( const Ray& ray, Scene& scene, ColorXYZ& default_color, int depth);
};


#endif