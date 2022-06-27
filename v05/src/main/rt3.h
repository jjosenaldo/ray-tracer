#ifndef RT3_H
#define RT3_H

#include <climits>
#include <stdexcept>

struct RunningOptions {
    RunningOptions() : scene_filename{""}, outfile{""}, quick_render{false} {
        crop_window[0][0] = 0;
        crop_window[1][0] = INT_MAX;
        crop_window[0][1] = 0;
        crop_window[1][1] = INT_MAX;
    }

    int crop_window[2][2];
	std::string scene_filename;
	std::string outfile;
    bool quick_render;
};

RunningOptions parse_running_options(int argc, char * argv[]);

#endif // RT3_H
