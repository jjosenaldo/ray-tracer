#include "parser.hpp"

int main(){
	unique_ptr<Camera> camera;
	unique_ptr<Film> film;
	unique_ptr<Background> background;
	
	parseScene("inout/in.xml", camera, film, background);
	
	for(int row = 0; row < film->height; ++row){
		for(int col = 0; col < film->width; ++col){
			auto color = background->sample(float(row)/film->height, float(col)/film->width);
			film->setPixel(color,Point2{col,row});
		}
	}

	film->writeImg();
	return 0;
}