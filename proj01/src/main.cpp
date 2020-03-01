#include "parser.hpp"

int main(){
	unique_ptr<Camera> camera;
	unique_ptr<Film> film;
	parseScene("inout/in.xml", camera, film);
	return 0;
}