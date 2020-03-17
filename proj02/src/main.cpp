#include <iostream>

#include "cxxopts.hpp"
#include "parser.hpp"

using std::cout;
using std::endl;
using cxxopts::Options;
using cxxopts::ParseResult;

Options makeCmdLineOptions(int argc, char** argv){
	Options options = Options("./bin/rt.out", "Generates a image using the Ray Tracing Algorithm.");
	options.add_options()
        ("i,input", "Input file", cxxopts::value<string>()->default_value("descriptions/in.xml"))
        ("h,help", "Print this message");
    return options;
}

int main(int argc, char** argv){
	auto commandLineOptions = makeCmdLineOptions(argc, argv);
	auto parseResult = commandLineOptions.parse(argc, argv);

    if (parseResult.count("help")){
      cout << commandLineOptions.help() << endl;
      exit(0);
    }

    string inputFile = parseResult["input"].as<string>();
    Rt3 rt3 = parse(inputFile);

    auto camera = rt3.camera.get();
    auto scene = rt3.scene.get();

	int height = camera->film->height;
	int width = camera->film->width;
	
	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			auto color = scene->background->sample(float(col)/width, 1-float(row)/height); //(x,y)
			auto ray = camera->generateRay(row, col);
			cout << ray << endl;
			camera->film->setPixel(color,Point2<int>{.x=col,.y=row});
		}
	}

	camera->film->writeImg();
	return 0;
}