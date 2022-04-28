#include "../utils/image.h"
#include "../core/api.h"
#include "rt3.h"
#include <sstream>
#include <cxxopts.hpp>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;


RunningOptions parse_running_options(int argc, char * argv[]) {
    cxxopts::Options options(argv[0], "A simple ray-tracer");
    options
      .custom_help("[<options>]")
      .positional_help("<input_scene_file>")
      .show_positional_help();
    options.add_options()
        ("h,help", "Print this help text")
        ("c,cropwindow", "Specify an image cropping window", cxxopts::value<std::vector<float>>(), "<x0,x1,y0,y1>")
        ("q,quick", "Reduces quality parameters to render image quickly", cxxopts::value<bool>()->default_value("false")->implicit_value("true"))
        ("o,outfile", "Write the rendered image to <filename>", cxxopts::value<std::string>(), "<filename>")
        ("input_scene_file", "Scene file to be parsed", cxxopts::value<std::string>())
    ;

    options.parse_positional({"input_scene_file"});

    auto result = options.parse(argc, argv);

    RunningOptions running_opts;

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }

    if (result.count("cropwindow"))
    {
        vector<float> window_read = result["cropwindow"].as<vector<float>>();
        if (window_read.size() != 4) {
            cout << "Crop window must be four floats" << endl;
            exit(0);
        }

        for (float coord: window_read) {
            if (coord < 0 || coord > 1) {
                cout << "Crop window must be four floats between 0 and 1" << endl;
                exit(0);
            }
        }
        
        running_opts.crop_window[0][0] = window_read[0];
        running_opts.crop_window[0][1] = window_read[1];
        running_opts.crop_window[1][0] = window_read[2];
        running_opts.crop_window[1][1] = window_read[3];
    }
    
    running_opts.quick_render = result["quick"].as<bool>();
    
    if (result.count("outfile"))
    {
      running_opts.outfile = result["outfile"].as<string>();
    }
    
    running_opts.scene_filename = result["input_scene_file"].as<string>();
    return running_opts;
}

int main( int argc, char * argv[] ) {
    RunningOptions opt = parse_running_options(argc, argv);

    // Start API
    API::init_engine(opt);
    API::run();
    API::clean_up();

    return 0;
}