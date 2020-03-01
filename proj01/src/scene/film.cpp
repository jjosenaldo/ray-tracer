#include "film.hpp"

Film::Film(int height, int width){
	this->height = height;
	this->width = width;
	this->buff = new int**[height];

	for(int y = 0; y < height; ++y){
		this->buff[y] = new int*[width];

		for(int x = 0; x < width; ++x)
			this->buff[y][x] = new int[3];
	}

	this->type = FT_IMAGE;
	string imgType = "ppm";
	string filename = "output.ppm";
}

Film::Film(ParamSet ps) : Film(ps.find_one("yRes", 500), ps.find_one("xRes", 500)) {}

Film::~Film(){
	if(this->buff == NULL) 
		return;

	this->buff = new int**[height];

	for(int y = 0; y < height; ++y){
		this->buff[y] = new int*[width];

		for(int x = 0; x < width; ++x)
			delete[] this->buff[y][x];

		delete[] this->buff[y];
	}

	delete[] this->buff;
}

void Film::setPixel( RgbColor color, int row, int col ){
	this->buff[row][col][0] = color.r;
	this->buff[row][col][1] = color.g;
	this->buff[row][col][2] = color.b;
}