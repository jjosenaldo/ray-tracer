#include "parser.hpp"

int main(){
	unique_ptr<Camera> camera;
	unique_ptr<Film> film;
	unique_ptr<Background> background;
	
	parseScene("inout/in.xml", camera, film, background);
	
	for(int row = film->height-1; row >=0 ; --row){
		for(int col = 0; col < film->width; ++col){
			auto color = background->sample(float(col)/film->width, float(row)/film->height); //(x,y)
			film->setPixel(color,Point2{row,col});
		}
	}

	film->writeImg();
	return 0;
}