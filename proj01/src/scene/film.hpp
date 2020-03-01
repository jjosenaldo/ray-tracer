#ifndef FILM_HPP
#define FILM_HPP

#include <string>
#include "color.hpp"
#include "paramset.hpp"

using std::string;

enum FilmType{
	FT_IMAGE
};

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
	Film(int width, int height);
	void setPixel( RgbColor color, int row, int col );

};

#endif