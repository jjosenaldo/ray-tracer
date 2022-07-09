#include "blinn_phong_integrator.h"
#include "blinn_phong_material.h"

BlinnPhongIntegrator::BlinnPhongIntegrator(Camera* camera, int _depth): SamplerIntegrator(camera), depth(_depth) { }

void BlinnPhongIntegrator::set_lights(vector<Light*> lights) {
    this->lights = lights;
}


ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color) {
    return Li(ray, scene, default_color, 0);
}

#include <iostream>
#include <cstdlib>
using namespace std;

ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color, int depth) {
    auto L = default_color;

    ColorXYZ radiance;
    Surfel isect;
    
    // TODO: actually use those two guys for something
    Vector3f wi;
    VisibilityTester vis;

    if (scene.intersect(ray, &isect)) {
            // cout << "ray: origin=" << ray.origin[0] << " " << ray.origin[1] << " " << ray.origin[2]; 
            // cout << ", dir=" << ray.direction[0] << " " << ray.direction[1] << " " << ray.direction[2]; 
            // cout << ", hit point: " << isect.p[0] << " " << isect.p[1] << " " << isect.p[2] << endl;
        
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
                auto shadow_ray_origin = isect.p;
                auto shadow_ray_dest = light->max_shadow_ray_point(isect.p);
                auto shadow_ray_direction = shadow_ray_dest - shadow_ray_origin;
                auto shadow_ray = Ray(shadow_ray_origin, shadow_ray_direction);
                Surfel isect2;
                auto min_t = 0.001;
                auto max_t = (shadow_ray_dest-shadow_ray_origin)[0] / shadow_ray_direction[0];
                // cout << "checking interesection for origin=";
                // cout << shadow_ray_origin[0] << " " << shadow_ray_origin[1] << " " << shadow_ray_origin[2];
                // cout << ", dest=";
                // cout << shadow_ray_dest[0] << " " << shadow_ray_dest[1] << " " << shadow_ray_dest[2];
                // cout << ", min_t=" << min_t << ", max_t=" << max_t << endl;

                if (scene.intersect(shadow_ray, &isect2, min_t, max_t)) {
                    // cout << "HIT: t=" << isect2.time << ", p=";
                    // cout << isect2.p[0] << " " << isect2.p[1] << " " << isect2.p[2];
                    // cout << endl;
                    continue;
                }

                L = L + light->sample_Li(isect, *bf_material, &wi, &vis);
            }
        }
        // TODO: cast shadows
        // TODO: Mirror (i.e. use the depth parameter for something)
    }

    return L;
}