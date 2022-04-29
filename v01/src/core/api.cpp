#include <iostream>
#include "api.h"
#include "error.h"
#include "vec3.h"

RunningOptions API::run_opt;
Camera API::m_camera;
Background API::m_background;

void API::init_engine( const RunningOptions & opt ) {
   run_opt = opt;
   std::clog << "Engine Initialized.\n";
}

void API::run( void ) {
	std::clog << ">>> Start API::run()\n";
    clog << "Parsing.\n";
    parse( run_opt.scene_filename.c_str() );
}

void API::clean_up( void ) {
    clog << "Cleaning free space.\n";
    //TODO Cleaning
}

void API::reset_engine( void ) {
	std::clog << ">>> Start API::reset_engine().\n";
}

void API::camera( const ParamSet& ps ) {
    std::clog << ">>> Start API::camera().\n";
	auto type = retrieve<string>(ps, "type", ""); // TODO
}

void API::film( const ParamSet& ps ) {
	std::clog << ">>> Start API::film()\n";

    auto filename = retrieve<string>(ps, "filename", ""); 
    auto img_type = retrieve<string>(ps, "img_type", "ppm3");
    auto type = retrieve<string>(ps, "type", "");
    auto x_res = retrieve<int>(ps, "x_res", -1);
    auto y_res = retrieve<int>(ps, "y_res", -1);

    if (x_res < 0 || y_res < 0) {
        RT3_ERROR("Invalid film size!");
    }

    if (img_type != "ppm3") {
        RT3_ERROR("Unsupported image type " + img_type + "! It must be ppm3.");
    }

    if (run_opt.outfile != "") {
        filename = run_opt.outfile; 
    }

    if (filename == "") {
        RT3_ERROR("Invalid file name!");
    }

    m_camera.film = Film(x_res, y_res, img_type, filename);
}

void API::background( const ParamSet& ps ) {
	std::clog << ">>> Start API::background()\n";
    
    auto tl = retrieve(ps, "tl", default_colorxyz()) / m_camera.film.max_color_value;
    auto tr = retrieve(ps, "tr", default_colorxyz()) / m_camera.film.max_color_value;
    auto bl = retrieve(ps, "bl", default_colorxyz()) / m_camera.film.max_color_value;
    auto br = retrieve(ps, "br", default_colorxyz()) / m_camera.film.max_color_value;
    auto color = retrieve(ps, "color", default_colorxyz()) / m_camera.film.max_color_value;
    auto type = retrieve<string>(ps, "type", ""); // TODO
    auto mapping = retrieve<string>(ps, "mapping", ""); // TODO

    if (!is_colorxyz_default(color)) {
        m_background = Background(color);
    } else if (!is_colorxyz_default(tl) && !is_colorxyz_default(tr) && !is_colorxyz_default(br) && !is_colorxyz_default(bl)) {
        m_background = Background(bl, tl, tr, br);
    } else {
        RT3_ERROR("It is necessary to pass either a single color or four colors!");
    }
}

void API::integrator( const ParamSet& ps ) {
	std::clog << ">>> Start API::integrator()\n";
    // TODO
}

void API::look_at( const ParamSet& ps ) {
	std::clog << ">>> Start API::look_at()\n";
    // TODO
}

void API::world_begin( void ) {
	std::clog << ">>> Start API::world_begin()\n";
    // TODO
}

void API::world_end( void )
{
	std::clog << ">>> Start API::world_end()\n";

	render();
	reset_engine();
}

void API::render( void ) {
	std::clog << ">>> Start API::render()\n";

	auto width = m_camera.film.width;
    auto height = m_camera.film.height;
    
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            auto color = m_background.sample(Point2f{float(i)/float(width), float(j)/float(height)});
            m_camera.film.add(Point2i{i, j}, color);
        }
    }

    m_camera.film.write_image();
}