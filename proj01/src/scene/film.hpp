#ifndef FILM_HPP
#define FILM_HPP

#include <string>

#include "linearalgebra.hpp"
#include "paramset.hpp"

using std::string;

enum FilmType{
	FT_IMAGE
};

FilmType filmTypeFromString(string str);

class Film{
public:
	int width;
	int height;
	float*** buff;
	FilmType type;
	string filename;
	string imgType;
	~Film();
	Film(ParamSet ps);
	Film(int height, int width, string filename, string imgType, FilmType type);
	void setPixel( RgbColorChar color, int row, int col );
	void setPixel(RgbColorChar, Point2<int> p);
	void writeImg();

};

#endif