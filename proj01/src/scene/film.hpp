#ifndef FILM_HPP
#define FILM_HPP

#include <string>
#include "color.hpp"
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
	int*** buff;
	FilmType type;
	string filename;
	string imgType;
	~Film();
	Film(ParamSet ps);
	Film(int height, int width, string filename, string imgType, FilmType type);
	void setPixel( RgbColor color, int row, int col );
	void setPixel(RgbColor, Point2 p);
	void writeImg();

};

#endif