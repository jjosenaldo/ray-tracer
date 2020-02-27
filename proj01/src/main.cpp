#include "parser.hpp"

int main(){
	unique_ptr<Camera> camera;
	parseScene("inout/in.xml", camera);
	return 0;
}