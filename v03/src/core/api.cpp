#include <iomanip>      // std::setprecision
#include <iostream>
#include "api.h"
#include "error.h"
#include "vec3.h"

RunningOptions API::run_opt;
Camera* API::m_camera;
LookAt* API::lookat_info;
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
    delete m_camera;
    // TODO
}

void API::reset_engine( void ) {
	std::clog << ">>> Start API::reset_engine().\n";
}

void API::camera( const ParamSet& ps ) {
    std::clog << ">>> Start API::camera().\n";
	auto type = retrieve<string>(ps, "type", "");


    if (type == "orthographic") {
        auto screen_window = retrieve(ps, "screen_window", vector<float>());
        if (screen_window.size() != 4) {
            RT3_ERROR("Invalid screen window! It must consist of 4 floats.");
        }

        m_camera = new OrthographicCamera(screen_window[0], screen_window[1], screen_window[2], screen_window[3], lookat_info);
    } else if (type == "perspective") {
        auto fovy = retrieve<float>(ps, "fovy", -1);
        auto screen_window = retrieve(ps, "screen_window", vector<float>());

        if (screen_window.size() != 4 && fovy < 0) {
            RT3_ERROR("For perspective cameras you must either provide a fovy or a screen space!");
        } 

        if (screen_window.size() == 4) {
            m_camera = new PerspectiveCamera(screen_window[0], screen_window[1], screen_window[2], screen_window[3], lookat_info);
        } else {
            auto focal_distance = retrieve(ps, "focal_distance", 1.0);
            auto aspect_ratio = retrieve(ps, "frame_aspectratio", -1.0);
            
            m_camera = new PerspectiveCamera(focal_distance, aspect_ratio, fovy, lookat_info);
        }
    } else {
        RT3_ERROR("Camera type " + type + " invalid! It must be ortographic or perspective.");
    }   
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

    if (run_opt.quick_render) {
        x_res /= 4;
        y_res /= 4;
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

    m_camera->film = Film(x_res, y_res, img_type, filename);

    auto maybe_perspective_m_camera_ptr = dynamic_cast<PerspectiveCamera*>(m_camera);
    if (maybe_perspective_m_camera_ptr) {
        maybe_perspective_m_camera_ptr->set_lrbt_from_xres_yres_if_needed();
    }

    m_camera->calculate_frame();
}

void API::background( const ParamSet& ps ) {
	std::clog << ">>> Start API::background()\n";
    
    auto tl = retrieve(ps, "tl", default_colorxyz()) / m_camera->film.max_color_value;
    auto tr = retrieve(ps, "tr", default_colorxyz()) / m_camera->film.max_color_value;
    auto bl = retrieve(ps, "bl", default_colorxyz()) / m_camera->film.max_color_value;
    auto br = retrieve(ps, "br", default_colorxyz()) / m_camera->film.max_color_value;
    auto color = retrieve(ps, "color", default_colorxyz()) / m_camera->film.max_color_value;
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
    auto type = retrieve<string>(ps, "type", "");
    // TODO
}

void API::look_at( const ParamSet& ps ) {
	std::clog << ">>> Start API::look_at()\n";
    auto look_from = retrieve<Point3f>(ps, "look_from", default_point3f());
    auto look_at = retrieve<Vector3f>(ps, "look_at", default_vector3f());
    auto up = retrieve<Vector3f>(ps, "up", default_vector3f());

    if (is_point3f_default(look_from)) RT3_ERROR("look_from information invalid or missing!");
    if (is_vector3f_default(look_at)) RT3_ERROR("look_at information invalid or missing!");
    if (is_vector3f_default(up)) RT3_ERROR("up information invalid or missing!");

    lookat_info = new LookAt(look_from, look_at, up);
}

void API::material( const ParamSet& ps ) {
	std::clog << ">>> Start API::material()\n";
    auto type = retrieve<string>(ps, "type", "");
    auto color = retrieve(ps, "color", default_colorxyz());

    // TODO
}

void API::object( const ParamSet& ps ) {
	std::clog << ">>> Start API::object()\n";
    auto type = retrieve<string>(ps, "type", "");
    auto radius = retrieve<float>(ps, "radius", 0.0);
    auto center = retrieve<Point3f>(ps, "center", default_point3f());
    
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

	auto width = m_camera->film.width;
    auto height = m_camera->film.height;
    
    for (int j = std::min(run_opt.crop_window[0][1], run_opt.crop_window[1][1]); j < std::min(height, std::max(run_opt.crop_window[0][1], run_opt.crop_window[1][1])); ++j) {
        for (int i = std::min(run_opt.crop_window[0][0], run_opt.crop_window[1][0]); i < std::min(width, std::max(run_opt.crop_window[0][0], run_opt.crop_window[1][0])); ++i) {
            Ray ray = m_camera->generate_ray(i, j);
            auto color = m_background.sample(Point2f{float(i)/float(width), float(j)/float(height)});
            m_camera->film.add(Point2i{i, j}, color);
        }
    }

    // vector<Point2i> inputs = {
    //     {0,1799},{700,1799},{1400,1799},{2100,1799},
    //     {0,1798},{700,1798},{1400,1798},{2100,1798},
    //     {0,1797},{700,1797},{1400,1797},{2100,1797},
    //     {0,2},{700,2},{1400,2},{2100,2},{2799,2},
    //     {0,1},{700,1},{1400,1},{2100,1},{2799,1},
    //     {0,0},{700,0},{1400,0},{2100,0},{2799,0}
    // };

    // std::cout << std::fixed << std::showpoint;
    // std::cout << std::setprecision(6);

    // std::cout << "e = [" << m_camera->frame->e[0] << " " << m_camera->frame->e[1] << " " << m_camera->frame->e[2] << "]" << std::endl;
    // std::cout << "w = [" << m_camera->frame->w[0] << " " << m_camera->frame->w[1] << " " << m_camera->frame->w[2] << "]" << std::endl;
    // std::cout << "u = [" << m_camera->frame->u[0] << " " << m_camera->frame->u[1] << " " << m_camera->frame->u[2] << "]" << std::endl;
    // std::cout << "v = [" << m_camera->frame->v[0] << " " << m_camera->frame->v[1] << " " << m_camera->frame->v[2] << "]" << std::endl;

    // std::cout << std::endl;

    // for (auto input : inputs) {
    //     auto i = input[0];
    //     auto j = input[1];
    //     Ray ray = m_camera->generate_ray(i, j);
    //     auto uv = m_camera->map_to_screen_space(input);
    //     std::cout << "i=" << i << " j=" << j << " u=" << uv[0] << " v=" << uv[1] << endl << ray.origin[0] << " " << ray.origin[1] << " " << ray.origin[2] << " "
    //     << ray.direction[0] << " " << ray.direction[1] << " " << ray.direction[2] << endl;
    // }
    

    m_camera->film.write_image();
}
