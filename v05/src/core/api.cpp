#include <iomanip>      // std::setprecision
#include <iostream>
#include "api.h"
#include "error.h"
#include "flat_material.h"
#include "vec3.h"
#include "sphere.h"
#include "flat_integrator.h"
#include "aggregate_primitive.h"
#include "blinn_phong_integrator.h"
#include "point_light.h"
#include "directional_light.h"

RunningOptions API::run_opt;
Camera* API::m_camera;
LookAt* API::lookat_info;
ObjectManager API::obj_manager;
Integrator* API::m_integrator;
Scene* API::scene;
vector<Light*> API::lights;

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
    delete lookat_info;
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
        scene->background = new Background(color);
    } else if (!is_colorxyz_default(tl) && !is_colorxyz_default(tr) && !is_colorxyz_default(br) && !is_colorxyz_default(bl)) {
        scene->background = new Background(bl, tl, tr, br);
    } else {
        RT3_ERROR("It is necessary to pass either a single color or four colors!");
    }
}

void API::integrator( const ParamSet& ps ) {
	std::clog << ">>> Start API::integrator()\n";
    auto type = retrieve<string>(ps, "type", "");
    
    if (type == "flat") {
        m_integrator = new FlatIntegrator(m_camera);
    } else if (type == "blinn_phong") {
        auto depth = retrieve<int>(ps, "depth", 1);
        m_integrator = new BlinnPhongIntegrator(m_camera, depth);
    } else {
        RT3_ERROR("Unsupported integrator type: " + type);
    }
}

void API::light( const ParamSet& ps ) {
	std::clog << ">>> Start API::light()\n";
    auto type = retrieve<string>(ps, "type", "");
    
    if (type == "point") {
        auto I = retrieve<ColorXYZ>(ps, "I", default_colorxyz());
        if (is_colorxyz_default(I)) {
            RT3_ERROR("\"I\" parameter missing for point light");    
        }

        auto scale = retrieve<ColorXYZ>(ps, "scale", default_colorxyz());
        if (is_colorxyz_default(scale)) {
            RT3_ERROR("\"scale\" parameter missing for point light");    
        }

        auto from = retrieve<Point3f>(ps, "from", default_point3f());
        if (is_point3f_default(from)) {
            RT3_ERROR("\"from\" parameter missing for point light");    
        }

        // TODO: actually do something with the scale
        lights.push_back(new PointLight(I, from, scale));
    } else if(type == "directional") {
        auto L = retrieve<ColorXYZ>(ps, "L", default_colorxyz());
        if (is_colorxyz_default(L)) {
            RT3_ERROR("\"L\" parameter missing for directional light");    
        }

        auto scale = retrieve<ColorXYZ>(ps, "scale", default_colorxyz());
        if (is_colorxyz_default(scale)) {
            RT3_ERROR("\"scale\" parameter missing for directional light");    
        }

        auto from = retrieve<Point3f>(ps, "from", default_point3f());
        if (is_point3f_default(from)) {
            RT3_ERROR("\"from\" parameter missing for directional light");    
        }

        auto to = retrieve<Point3f>(ps, "to", default_point3f());
        if (is_point3f_default(to)) {
            RT3_ERROR("\"to\" parameter missing for directional light");    
        }

        // TODO: actually do something with the scale
        lights.push_back(new DirectionalLight(L, from, to, scale));
    } else if(type == "spot") {
        auto I = retrieve<ColorXYZ>(ps, "I", default_colorxyz());
        if (is_colorxyz_default(I)) {
            RT3_ERROR("\"I\" parameter missing for spot light");    
        }

        auto scale = retrieve<ColorXYZ>(ps, "scale", default_colorxyz());
        if (is_colorxyz_default(scale)) {
            RT3_ERROR("\"scale\" parameter missing for spot light");    
        }

        auto from = retrieve<Point3f>(ps, "from", default_point3f());
        if (is_point3f_default(from)) {
            RT3_ERROR("\"from\" parameter missing for spot light");    
        }

        auto to = retrieve<Point3f>(ps, "to", default_point3f());
        if (is_point3f_default(to)) {
            RT3_ERROR("\"to\" parameter missing for spot light");    
        }

        auto cutoff = retrieve<int>(ps, "cutoff", 1);
        auto falloff = retrieve<int>(ps, "falloff", 1);

        //lights.push_back(new SpotlLight(I, from, to, scale));

    }
    else {
        RT3_ERROR("Unsupported light source type: " + type);
    }
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
    Material* mat;

    if (type == "flat") {
        mat = new FlatMaterial(color);
    } else if (type == "blinn") {
        auto name = retrieve<string>(ps, "name", "");

        auto ambient = retrieve<ColorXYZ>(ps, "ambient", default_colorxyz());
        if (is_colorxyz_default(ambient)) RT3_ERROR("Missing \"ambient\" parameter in Blinn material");

        auto diffuse = retrieve<ColorXYZ>(ps, "diffuse", default_colorxyz());
        if (is_colorxyz_default(diffuse)) RT3_ERROR("Missing \"diffuse\" parameter in Blinn material");

        auto specular = retrieve<ColorXYZ>(ps, "specular", default_colorxyz());
        if (is_colorxyz_default(specular)) RT3_ERROR("Missing \"specular\" parameter in Blinn material");

        auto mirror = retrieve<ColorXYZ>(ps, "mirror", default_colorxyz());
        if (is_colorxyz_default(mirror)) RT3_ERROR("Missing \"mirror\" parameter in Blinn material");

        auto glossiness = retrieve<int>(ps, "glossiness", 1);

        mat = new BlinnPhongMaterial(ambient, diffuse, specular, mirror, glossiness);
    } else {
        RT3_ERROR("Unsupported material type: " + type);
    }

     
    obj_manager.add_material(mat);
}

void API::object( const ParamSet& ps ) {
	std::clog << ">>> Start API::object()\n";
    auto type = retrieve<string>(ps, "type", "");

    if( type == "sphere") {
        auto radius = retrieve<float>(ps, "radius", 0.0);
        auto center = retrieve<Point3f>(ps, "center", default_point3f());
        obj_manager.instantiate_sphere(center, radius, obj_manager.get_material());
    } else if (type == "triangle") {
        auto p1 = retrieve<Point3f>(ps, "p1", default_point3f());
        if (is_point3f_default(p1)) RT3_ERROR("Missing parameter \"p1\" for plane");
        auto p2 = retrieve<Point3f>(ps, "p2", default_point3f());
        if (is_point3f_default(p2)) RT3_ERROR("Missing parameter \"p2\" for plane");
        auto p3 = retrieve<Point3f>(ps, "p3", default_point3f());
        if (is_point3f_default(p3)) RT3_ERROR("Missing parameter \"p3\" for plane");

        obj_manager.instantiate_triangle(p1, p2, p3, obj_manager.get_material());
    } else {
        RT3_ERROR("Unsupported object type: " + type);
    }
}

void API::world_begin( void ) {
	std::clog << ">>> Start API::world_begin()\n";
    scene = new Scene();
}

void API::world_end( void )
{
	std::clog << ">>> Start API::world_end()\n";

    scene->aggregate = new AggregatePrimitive(obj_manager.get_object_list());

    BlinnPhongIntegrator *bf_integrator = dynamic_cast< BlinnPhongIntegrator *>( m_integrator);
    if (bf_integrator) bf_integrator->set_lights(lights);

    m_integrator->render(*scene);
	reset_engine();
}