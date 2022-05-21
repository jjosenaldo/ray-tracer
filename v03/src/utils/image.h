#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <functional>
#include <iostream>
#include "math.h"
#include "vec3.h"

using std::function;
using std::ostream;
using std::ofstream;

struct RgbColor
{
    int r;
    int g;
    int b;

    friend ostream &operator<<(ostream &os, const RgbColor &color);
    friend RgbColor operator*(const RgbColor& color, const int& i);
    friend RgbColor operator/(const RgbColor& color, const int& i);
    friend RgbColor operator+(const RgbColor& color1, const RgbColor& color2);
};

struct Pixel
{
    RgbColor color;
    Point2f point;

    int x() const;
    int y() const;
    friend ostream &operator<<(ostream &os, const Pixel &pixel);
};

class PpmImage {
    private:
        int width;
        int height;
        int max_color_value;
        Pixel** pixels;

    public:
        PpmImage(int width, int height, int max_color_value, Pixel tl, Pixel bl, Pixel br, Pixel tr);
        ~PpmImage();

        void write_to_stream(ofstream& stream);
};

#endif