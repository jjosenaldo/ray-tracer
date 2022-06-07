#include "flat_integrator.h"
#include "flat_material.h"
#include "surfel.h"

ColorXYZ FlatIntegrator::Li(const Ray& ray, const Scene& scene, ColorXYZ& default_color ) {
    ColorXYZ radiance;
    Surfel isect;

    if (!scene.intersect(ray, &isect)) {
        radiance = default_color;
    } else {
        FlatMaterial *fm = dynamic_cast< FlatMaterial *>( isect.primitive->get_material());
        if (fm) {
            radiance = fm->kd();
        }
    }

    return radiance;
}