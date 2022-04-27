#include "../utils/image.h"
#include "../core/rt3.h"
#include "../core/api.h"
#include <sstream>

using std::cout;
using std::endl;

void usage(const char *msg=nullptr ) {
    if ( msg ) std::cerr << "RT3: " << msg << "\n\n";

    std::cerr << "Usage: rt3 [<options>] <input_scene_file>\n"
        << "  Rendering simulation options:\n"
        << "    --help                     Print this help text.\n"
        << "    --cropwindow <x0,x1,y0,y1> Specify an image crop window.\n"
        << "    --quick                    Reduces quality parameters to render image quickly.\n"
        << "    --outfile <filename>       Write the rendered image to <filename>.\n\n";
    exit( msg ? 1 : 0 );
}

int main( int argc, char * argv[] ) {
    RunningOptions opt;

    // No input arguments.
    if (argc == 1) usage();

    // Beginning parsing arguments.
    std::ostringstream oss;

    // TODO add try and catch to each value atribuition
    for (int i=1; i < argc; i++) {
        std::string option = argv[i];
        if (option == "--cropwindow") {
            if (i+4 >= argc) usage( "not enough values for --cropwindow argument");

            opt.crop_window[0][0] = std::stof(argv[++i]);
            opt.crop_window[0][1] = std::stof(argv[++i]);
            opt.crop_window[1][0] = std::stof(argv[++i]);
            opt.crop_window[1][1] = std::stof(argv[++i]);
        } else if (option == "--outfile") {
            if (i+1 == argc) usage( "missing value for --outfile argument");
            opt.outfile = std::string(argv[++i]);
        } else if (option == "--quickrender") {
            opt.quick_render = true;
        } else if (option == "--help") {
            usage();
        } else {
            opt.scene_filename = std::string(argv[i]);

            std::ifstream scene_file_ifs { opt.scene_filename };

            if (!scene_file_ifs.is_open()) {
                std::ostringstream oss;
                oss << "Error! Could not open file [" << opt.scene_filename << "].\n";
            }
            scene_file_ifs.close();
        }
    } // finish parsing arguments

    // Start API
    API::init_engine(opt);
    API::run();
    API::clean_up();

    return 0;
}
