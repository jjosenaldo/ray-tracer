#include <stdexcept>
#ifndef RT3_H
#define RT3_H

#include <vector> //Try later using own vector instead

struct RunningOptions {
    RunningOptions() : scene_filename{""}, outfile{""}, quick_render{false} {
        crop_window[0][0] = 0;
        crop_window[0][1] = 1;
        crop_window[1][0] = 0;
        crop_window[1][1] = 1;
    }

    float crop_window[2][2];
	std::string scene_filename;
	std::string outfile;
    bool quick_render;
};

#endif // RT3_H
