#include "api.h"
#include <iostream>

RunningOptions API::run_opt;

void API::init_engine( const RunningOptions & opt ) {
   run_opt = opt;
   cout << "Engine Initialized.\n";
}

void API::run( void ) {
	std::cout << ">>> Start API::run()\n";
    cout << "Parsing.\n";
    parse( run_opt.scene_filename.c_str() );
}

void API::clean_up( void ) {
    cout << "Cleaning free space.\n";
    //TODO Cleaning
}

void API::reset_engine( void ) {
	std::cout << ">>> Start API::reset_engine().\n";
}

void API::camera( const ParamSet& ps ) {
	std::cout << ">>> Start API::camera()\n";
    // TODO
}

void API::film( const ParamSet& ps ) {
	std::cout << ">>> Start API::film()\n";
    // TODO
}

void API::background( const ParamSet& ps ) {
	std::cout << ">>> Start API::background()\n";
    // TODO
}

void API::integrator( const ParamSet& ps ) {
	std::cout << ">>> Start API::integrator()\n";
    // TODO
}

void API::look_at( const ParamSet& ps ) {
	std::cout << ">>> Start API::look_at()\n";
    // TODO
}

void API::world_begin( void ) {
	std::cout << ">>> Start API::world_begin()\n";
    // TODO
}

void API::world_end( void )
{
    /** TODO
     * Gerar tudo. Camera, Film, Background etc etc.
	 * Após sua geraccao, usar as informacoes para renderizar a cena.
     */

	std::cout << ">>> Start API::world_end()\n";

	render();
	reset_engine();
}

void API::render( void ) {
	std::cout << ">>> Start API::render()\n";

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
