#include <iostream>
#include "api.h"
#include "error.h"
#include "vec3.h"

using std::cout;
using std::endl;

RunningOptions API::run_opt;
Camera API::m_camera;
Background API::m_background;

void API::init_engine( const RunningOptions & opt ) {
   run_opt = opt;
   cout << "Engine Initialized.\n";
}

void API::run( void ) {
	std::cout << ">>> Start API::run()\n";
    cout << "Parsing.\n";
    parse( run_opt.scene_filename.c_str() );
}

void API::clean_up( void ) {
    cout << "Cleaning free space.\n";
    //TODO Cleaning
}

void API::reset_engine( void ) {
	std::cout << ">>> Start API::reset_engine().\n";
}

void API::camera( const ParamSet& ps ) {
	auto type = retrieve<string>(ps, "type", ""); // TODO: what to do with this?
    // TODO
}

void API::film( const ParamSet& ps ) {
	std::cout << ">>> Start API::film()\n";

    auto filename = retrieve<string>(ps, "filename", ""); // TODO: what to do with this?
    auto img_type = retrieve<string>(ps, "img_type", ""); // TODO: what to do with this?
    auto type = retrieve<string>(ps, "type", ""); // TODO: what to do with this?
    auto x_res = retrieve<int>(ps, "x_res", -1); // TODO: what to do with this?
    auto y_res = retrieve<int>(ps, "y_res", -1); // TODO: what to do with this?

    if (x_res < 0 || y_res < 0) {
        RT3_ERROR("Invalid film size!");
    }

    if (img_type != "ppm") {
        RT3_ERROR("Unsupported image type! It must be ppm.");
    }

    m_camera.film.filename = run_opt.scene_filename != "" ? run_opt.scene_filename : filename;

    if (m_camera.film.filename == "") {
        RT3_ERROR("Invalid file name!");
    }

    m_camera.film.width = x_res;
    m_camera.film.height = y_res;
}

void API::background( const ParamSet& ps ) {
	std::cout << ">>> Start API::background()\n";
    
    auto tl = retrieve(ps, "tl", default_colorxyz());
    auto tr = retrieve(ps, "tr", default_colorxyz());
    auto bl = retrieve(ps, "bl", default_colorxyz());
    auto br = retrieve(ps, "br", default_colorxyz());
    auto color = retrieve(ps, "color", default_colorxyz());
    auto type = retrieve<string>(ps, "type", ""); // TODO: what to do with this?
    auto mapping = retrieve<string>(ps, "mapping", ""); // TODO: what to do with this?

    if (!is_colorxyz_default(color)) {
        m_background = Background(color);
    } else if (!is_colorxyz_default(tl) && !is_colorxyz_default(tr) && !is_colorxyz_default(br) && !is_colorxyz_default(bl)) {
        m_background = Background(bl, tl, tr, br);
    } else {
        RT3_ERROR("It is necessary to pass either a single color or four colors!");
    }
}

void API::integrator( const ParamSet& ps ) {
	std::cout << ">>> Start API::integrator()\n";
    // TODO
}

void API::look_at( const ParamSet& ps ) {
	std::cout << ">>> Start API::look_at()\n";
    // TODO
}

void API::world_begin( void ) {
	std::cout << ">>> Start API::world_begin()\n";
    // TODO
}

void API::world_end( void )
{
    /** TODO
     * Gerar tudo. Camera, Film, Background etc etc.
	 * Após sua geraccao, usar as informacoes para renderizar a cena.
     */

	std::cout << ">>> Start API::world_end()\n";

	render();
	reset_engine();
}

void API::render( void ) {
	std::cout << ">>> Start API::render()\n";

	int width = 500;
    int height = 500;
    int max_color_value = 255;

    // PpmImage ppm_image = PpmImage(width, height, max_color_value,
    //                               Pixel{RgbColor{255, 0, 0}, 0, height - 1},
    //                               Pixel{RgbColor{0, 255, 0}, 0, 0},
    //                               Pixel{RgbColor{0, 0, 255}, width - 1, 0},
    //                               Pixel{RgbColor{255, 255, 0}, width - 1, height - 1});

    ofstream output_image;
    output_image.open(run_opt.outfile != "" ? run_opt.outfile : m_camera.film.filename);
    // ppm_image.write_to_stream(output_image);
    output_image.close();
}