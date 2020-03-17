#include <algorithm>
#include <iostream>
#include <fstream>


#include "film.hpp"

using std::max;
using std::min;
using std::endl;
using std::ofstream;

FilmType filmTypeFromString(string str){
	if(str == "image") return FilmType::FT_IMAGE;


	return FilmType::FT_IMAGE;
}

Film::Film(int height, int width, string filename, string imgType, FilmType type){
	// std::cout << "Film::Film(params)_begin\n";
	this->height = height;
	this->width = width;
	this->buff = new float**[height];

	for(int y = 0; y < height; ++y){
		this->buff[y] = new float*[width];

		for(int x = 0; x < width; ++x)
			this->buff[y][x] = new float[3];
	}

	this->type = type;
	this->imgType = imgType;
	this->filename = filename;
	this->type = type;
	// std::cout << "Film::Film(params)_end\n";
}

Film::Film(ParamSet ps) : Film(
	ps.find_one<int>("yRes", 500), 
	ps.find_one<int>("xRes", 500), 
	ps.find_one<string>("filename", "output"), 
	ps.find_one<string>("imgType", "ppm"), 
	filmTypeFromString(ps.find_one<string>("type", "image"))
) {}

Film::~Film(){
	// std::cout << "Film::~Film()_begin\n";
	if(this->buff == NULL) 
		return;

	for(int y = 0; y < height; ++y){

		for(int x = 0; x < width; ++x)
			delete[] this->buff[y][x];

		delete[] this->buff[y];
	}

	delete[] this->buff;
	// std::cout << "Film::~Film()_end\n";
}

void Film::setPixel( RgbColorChar color, int row, int col ){
	this->buff[row][col][0] = color.r() / float(255);
	this->buff[row][col][1] = color.g() / float(255);
	this->buff[row][col][2] = color.b() / float(255);
}

void Film::setPixel(RgbColorChar color, Point2<int> p){
	this->setPixel(color, p.y, p.x);
}

#define from01to255(x) max(0,min((int)(x*255),255))
void Film::writeImg(){
	ofstream outFile;
	outFile.open(filename+"."+imgType);
	outFile << "P3 " << width << " " << height << " " << 255 << endl;

	for(int row = 0; row < height; ++row){
		for(int col = 0; col < width; ++col){
			outFile << from01to255(buff[row][col][0]) << " " 
					<< from01to255(buff[row][col][1]) << " " 
					<< from01to255(buff[row][col][2]) << " ";
		}
		outFile << endl;
	}
}