#include <fstream>
#include <iostream>
#include "film.h"

using std::ofstream;

Film::Film() : Film(0, 0, "", "") { }

Film::Film(int width, int height, string img_type, string filename) {
    this->width = width;
    this->height = height;
    this->img_type = img_type;
    this->filename = filename;
    buffer = new ColorXYZ*[height];

    for (int j = 0; j < height; ++j) {
        buffer[j] = new ColorXYZ[width];
    }
}

void Film::add(Point2i point, ColorXYZ color) {
    buffer[point[1]][point[0]] = color;
}

void Film::write_image() {
    ofstream output_image;
    output_image.open(this->filename);

    if (this->img_type == "ppm3") {
        write_to_ppm(output_image);
    }
    
}

void Film::write_to_ppm(ofstream& stream) {  
    stream << "P3\n"
           << width << " " << height << "\n"
           << max_color_value << "\n";

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            auto color = buffer[i][j];
            stream << static_cast<int>(color[0]*max_color_value) << " " << static_cast<int>(color[1]*max_color_value) << " " << static_cast<int>(color[2]*max_color_value) << "\n";
        }
    }
}