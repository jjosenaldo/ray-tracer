#include "film.hpp"

FilmType filmTypeFromString(string str){
	if(str == "image") return FilmType::FT_IMAGE;


	return FilmType::FT_IMAGE;
}

Film::Film(int height, int width, string filename, string imgType, FilmType type){
	this->height = height;
	this->width = width;
	this->buff = new int**[height];

	for(int y = 0; y < height; ++y){
		this->buff[y] = new int*[width];

		for(int x = 0; x < width; ++x)
			this->buff[y][x] = new int[3];
	}

	this->type = type;
	this->imgType = imgType;
	this->filename = filename;
	this->type = type;
}

Film::Film(ParamSet ps) : Film(
	ps.find_one<int>("yRes", 500), 
	ps.find_one<int>("xRes", 500), 
	ps.find_one<string>("filename", "output"), 
	ps.find_one<string>("imgType", "ppm"), 
	filmTypeFromString(ps.find_one<string>("type", "image"))
) {}

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