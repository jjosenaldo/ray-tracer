#include "parser.hpp"

int main(){
	unique_ptr<Camera> camera;
	unique_ptr<Background> background;
	
	parseScene("inout/in.xml", camera, background);
	int height = camera->film->height;
	int width = camera->film->width;
	
	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			auto color = background->sample(float(col)/width, 1-float(row)/height); //(x,y)
			camera->film->setPixel(color,Point2{.x=col,.y=row});
		}
	}

	camera->film->writeImg();
	return 0;
}