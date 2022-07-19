#include "blinn_phong_integrator.h"
#include "blinn_phong_material.h"

BlinnPhongIntegrator::BlinnPhongIntegrator(Camera* camera, int _depth): SamplerIntegrator(camera), max_depth(_depth) { }

void BlinnPhongIntegrator::set_lights(vector<Light*> lights) {
    this->lights = lights;
}


ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color) {
    return Li(ray, scene, default_color, 1);
}

#include <cstdlib>

ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color, int curr_depth) {
    auto L = default_color;

    ColorXYZ radiance;
    Surfel isect;
    
    // TODO: actually use those two guys for something
    Vector3f wi;
    VisibilityTester vis;
    const float low_float = 1e-3;

    if (scene.intersect(ray, &isect)) {
            // cout << "ray: origin=" << ray.origin[0] << " " << ray.origin[1] << " " << ray.origin[2]; 
            // cout << ", dir=" << ray.direction[0] << " " << ray.direction[1] << " " << ray.direction[2]; 
            // cout << ", hit point: " << isect.p[0] << " " << isect.p[1] << " " << isect.p[2] << endl;
        
        L = {0.0f, 0.0f, 0.0f};

        // hitting from behind
        if(dot_vector3f(isect.wo, isect.n) < 0) return L;

        BlinnPhongMaterial *bf_material = dynamic_cast< BlinnPhongMaterial *>( isect.primitive->get_material());
        if (bf_material) {
            for (auto light: lights) {
                auto shadow_ray_origin = isect.p;
                auto shadow_ray_dest = light->max_shadow_ray_point(isect.p);
                auto shadow_ray_direction = shadow_ray_dest - shadow_ray_origin;
                auto shadow_ray = Ray(shadow_ray_origin, shadow_ray_direction);
                Surfel isect2;
                auto min_t = 0.001;
                auto max_t = 1;
                if (scene.intersect(shadow_ray, &isect2, min_t, max_t)) {
                    continue;
                }

                L = L + light->sample_Li(isect, *bf_material, &wi, &vis);
            }

            if(curr_depth < max_depth) {
                Vector3f newDir = normalize_vector3f(ray.direction + (isect.n * (-2 * dot_vector3f(ray.direction, isect.n))));
                L = L + bf_material->mirror * Li(Ray(isect.p + newDir * low_float, newDir), scene, default_color, curr_depth + 1);
            }
        }
    }

    return L;
}