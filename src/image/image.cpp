#include "image.h"
#include "math.h"

ostream &operator<<(ostream &os, const RgbColor &color)
{
    os << "(" << color.r << " " << color.g << " " << color.b << ")";

    return os;
}

RgbColor operator*(const RgbColor &color, const int &i)
{
    return RgbColor{color.r * i, color.g * i, color.b * i};
}

RgbColor operator/(const RgbColor &color, const int &i)
{
    return RgbColor{color.r / i, color.g / i, color.b / i};
}

RgbColor operator+(const RgbColor &color1, const RgbColor &color2)
{
    return RgbColor{color1.r + color2.r, color1.g + color2.g, color1.b + color2.b};
}

ostream &operator<<(ostream &os, const Pixel &pixel)
{
    os << "(" << pixel.x() << "," << pixel.y() << ") = " << pixel.color;

    return os;
}

int Pixel::x() const
{
    return point.x;
}

int Pixel::y() const
{
    return point.y;
}

PpmImage::PpmImage(int width, int height, int max_color_value, Pixel tl, Pixel bl, Pixel br, Pixel tr)
{
    this->width = width;
    this->height = height;
    this->max_color_value = max_color_value;
    auto interpolation = bilinear_interpolation<RgbColor>(tl.point, bl.point, br.point, tr.point, tl.color, bl.color, br.color, tr.color);
    this->pixels = new Pixel *[height];

    for (int i = 0; i < height; ++i)
    {
        this->pixels[i] = new Pixel[width];

        for (int j = 0; j < width; ++j)
        {
            auto point = Point2{j, height - i};
            this->pixels[i][j] = Pixel{interpolation(point), point};
        }
    }
}

PpmImage::~PpmImage()
{
    for (int i = 0; i < this->height; ++i)
    {
        delete[] this->pixels[i];
    }
    delete[] this->pixels;
}

void PpmImage::write_to_stream(ofstream &stream)
{
    stream << "P3\n"
           << width << " " << height << "\n"
           << max_color_value << "\n";

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            Pixel pixel = pixels[i][j];
            stream << pixel.color.r << " " << pixel.color.g << " " << pixel.color.b << "\n";
        }
    }
}
