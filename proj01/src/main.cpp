#include "parser.hpp"

int main(){
	unique_ptr<Camera> camera;
	unique_ptr<Film> film;
	unique_ptr<Background> background;
	parseScene("inout/in.xml", camera, film, background);
	std::cout << +background->bl.r << " " << +background->bl.g << " " << +background->bl.b << "\n";
	std::cout << +background->tl.r << " " << +background->tl.g << " " << +background->tl.b << "\n";
	std::cout << +background->tr.r << " " << +background->tr.g << " " << +background->tr.b << "\n";
	std::cout << +background->br.r << " " << +background->br.g << " " << +background->br.b << "\n";
	return 0;
}