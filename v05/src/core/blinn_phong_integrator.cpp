#include "blinn_phong_integrator.h"
#include "blinn_phong_material.h"

BlinnPhongIntegrator::BlinnPhongIntegrator(Camera* camera, int _depth): SamplerIntegrator(camera), depth(_depth) { }

void BlinnPhongIntegrator::set_lights(vector<Light*> lights) {
    this->lights = lights;
}


ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color) {
    return Li(ray, scene, default_color, 0);
}

ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color, int depth) {
    auto L = default_color;

    ColorXYZ radiance;
    Surfel isect;
    
    // TODO: actually use those two guys for something
    Vector3f wi;
    VisibilityTester vis;

    if (scene.intersect(ray, &isect)) {
        // TODO: como exatamente checar isso? O raio atingir por trás é equivalente
        // ao ângulo entre o raio e a normal da superfície no ponto ser >90°? 
        // (esse ângulo ser 180° certamente significaria que a superfície foi atingida
        // por trás)
        //
        // [2] SPECIAL SITUATION: IF THE RAY HITS THE SURFACE FROM
        // "BEHIND" (INSIDE), WE DO NOT COLOR.
        L = {0.0f, 0.0f, 0.0f};

        BlinnPhongMaterial *bf_material = dynamic_cast< BlinnPhongMaterial *>( isect.primitive->get_material());
        if (bf_material) {
            for (auto light: lights) {
                L = L + light->sample_Li(isect, *bf_material, &wi, &vis);
            }
        }
        // TODO: cast shadows
        // TODO: Mirror (i.e. use the depth parameter for something)
    }

    return L;
}