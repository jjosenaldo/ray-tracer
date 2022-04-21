
#include "image.h"

using std::cout;
using std::endl;

int main()
{
    int width = 500;
    int height = 500;
    int max_color_value = 255;

    PpmImage ppm_image = PpmImage(width, height, max_color_value,
                                  Pixel{RgbColor{255, 0, 0}, 0, height - 1},
                                  Pixel{RgbColor{0, 255, 0}, 0, 0},
                                  Pixel{RgbColor{0, 0, 255}, width - 1, 0},
                                  Pixel{RgbColor{255, 255, 0}, width - 1, height - 1});

    ofstream output_image;

    output_image.open("output.ppm");
    ppm_image.write_to_stream(output_image);
    output_image.close();

    return 0;
}