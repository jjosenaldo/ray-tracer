#ifndef FILM_H
#define FILM_H

#include <fstream>
#include <string>
#include "vec3.h"

using std::ofstream;
using std::string;

class Film {
    private:
        ColorXYZ** buffer;
        string img_type;
        string filename;
        void write_to_ppm(ofstream& stream);

    public:
        int width;
        int height;
        int max_color_value = 255;

        Film();
        Film(int width, int height, string img_type, string filename);
	virtual ~Film() = default;
        void add(Point2i point, ColorXYZ color);
        void write_image();
};

#endif
