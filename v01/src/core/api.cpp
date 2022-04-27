#include "api.h"

void API::init_engine( const RunningOptions & opt ) {

   run_opt = opt;
   cout << "Engine Initialized.\n";
}

void API::run( void ) {
    cout << "Parsing.\n";
    parse( run_opt.scene_filename.c_str() );
}

void API::clean_up( void ) {
    cout << "Cleaning free space.\n";
    //TODO Cleaning
}

/* TODO

void API::camera( const ParamSet& ps ) {

}

void API::film( const ParamSet& ps ) {

}

void API::background( const ParamSet& ps ) {

}

void API::integrator( const ParamSet& ps ) {

}

void API::look_at( const ParamSet& ps ) {

}

void API::world_begin( void ) {
   
}
*/

void API::world_end( void )
{
    /** TODO
     * Gerar tudo. Camera, Film, Background etc etc.
     * De acordo com o pdf, esse seria o método render(),
     * porém o parser.cpp passado para nós o chama de world_end().
     */

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
}