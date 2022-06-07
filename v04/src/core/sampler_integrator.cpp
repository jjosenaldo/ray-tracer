#include <algorithm>
#include "sampler_integrator.h"

void SamplerIntegrator::render(const Scene& scene) {
    preprocess(scene);

    auto width = camera->film.width;
    auto height = camera->film.height;

    for (int j = std::min(run_opt.crop_window[0][1], run_opt.crop_window[1][1]); j < std::min(height, std::max(run_opt.crop_window[0][1], run_opt.crop_window[1][1])); ++j) {
        for (int i = std::min(run_opt.crop_window[0][0], run_opt.crop_window[1][0]); i < std::min(width, std::max(run_opt.crop_window[0][0], run_opt.crop_window[1][0])); ++i) {
            auto screen_coord = Point2f{float(i)/float(width), float(j)/float(height)};
            ColorXYZ background_color = scene.background->sample( screen_coord );
            Ray ray = camera->generate_ray(i, j);
            ColorXYZ final_color = Li( ray, scene, background_color );
            camera->film.add( Point2i{i,j}, final_color );
        }
    }

    camera->film.write_image();
}

void SamplerIntegrator::preprocess( const Scene& scene )  {
    // TODO
}