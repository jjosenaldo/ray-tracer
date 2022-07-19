#include "blinn_phong_integrator.h"
#include "blinn_phong_material.h"
#include "ambient_light.h"

BlinnPhongIntegrator::BlinnPhongIntegrator(Camera* camera, int _depth): SamplerIntegrator(camera), max_depth(_depth) { }

void BlinnPhongIntegrator::set_lights(vector<Light*> lights) {
    this->lights = lights;
}


ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color) {
    return Li(ray, scene, default_color, 1);
}

ColorXYZ BlinnPhongIntegrator::Li( const Ray& ray, Scene& scene, ColorXYZ& default_color, int curr_depth) {
    Surfel isect;
    
    // TODO: actually use those two guys for something
    Vector3f wi;
    VisibilityTester* vis;
    const float low_float = 1e-3;

    if (scene.intersect(ray, &isect)) {
            // cout << "ray: origin=" << ray.origin[0] << " " << ray.origin[1] << " " << ray.origin[2]; 
            // cout << ", dir=" << ray.direction[0] << " " << ray.direction[1] << " " << ray.direction[2]; 
            // cout << ", hit point: " << isect.p[0] << " " << isect.p[1] << " " << isect.p[2] << endl;
        
        ColorXYZ L = {0.0f, 0.0f, 0.0f};

        // hitting from behind
        if(dot_vector3f(isect.wo, isect.n) < 0) return L;

        BlinnPhongMaterial *bf_material = dynamic_cast< BlinnPhongMaterial *>( isect.primitive->get_material());
        if (bf_material) {
            for (auto light: lights) {
                
                /**
                 * TODO: would be more elegant to code AmbientLight::shadow_ray() in a way which
                 * scene.intersect(shadow_ray, &isect2, min_t, max_t) would never be true
                 * but this way works and time is money
                 */
                if(typeid(*light) == typeid(AmbientLight)) {
                    L = L + light->sample_Li(isect, *bf_material, &wi, vis);
                    continue;
                }
                auto shadow_ray = light->shadow_ray(isect.p);
                Surfel isect2;
                auto min_t = 0.001;
                /**
                 * TODO: maybe this should be higher for directional lights, since the limit is in theory
                 * some bounding box encompassing the scene. However, 1 is working fine for now.
                 */
                auto max_t = 1;
                if (scene.intersect(shadow_ray, &isect2, min_t, max_t)) {
                    continue;
                }

                ColorXYZ color = light->sample_Li(isect, *bf_material, &wi, vis);
                //if(vis->unoccluded(scene)) {
                    L = L + color;
                //}
            }

            if(curr_depth < max_depth) {
                Vector3f newDir = normalize_vector3f(ray.direction + (isect.n * (-2 * dot_vector3f(ray.direction, isect.n))));
                L = L + bf_material->mirror * Li(Ray(isect.p + newDir * low_float, newDir), scene, default_color, curr_depth + 1);
            }
        }
        
        return L;
    } else {
        return default_color;
    }
}