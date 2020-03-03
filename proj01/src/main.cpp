#include <iostream>

#include "cxxopts.hpp"
#include "parser.hpp"

using std::cout;
using std::endl;
using cxxopts::Options;
using cxxopts::ParseResult;

Options parseCmdlineOptions(int argc, char** argv){
	Options options = Options("./bin/rt.out", "Generates a image using the Ray Tracing Algorithm.");
	options.add_options()
        ("i,input", "Input file", cxxopts::value<string>()->default_value("inout/in.xml"))
        ("h,help", "Print this message");
    return options;
}

int main(int argc, char** argv){
	auto commandLineOptions = parseCmdlineOptions(argc, argv);
	auto parseResult = commandLineOptions.parse(argc, argv);

    if (parseResult.count("help")){
      cout << commandLineOptions.help() << endl;
      exit(0);
    }

    string inputFile = parseResult["input"].as<string>();

	unique_ptr<Camera> camera;
	unique_ptr<Scene> scene;
	
	parse(inputFile, camera, scene);
	int height = camera->film->height;
	int width = camera->film->width;
	
	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			auto color = scene->background->sample(float(col)/width, 1-float(row)/height); //(x,y)
			camera->film->setPixel(color,Point2<int>{.x=col,.y=row});
		}
	}

	camera->film->writeImg();
	return 0;
}