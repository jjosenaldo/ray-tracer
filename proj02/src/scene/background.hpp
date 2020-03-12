#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "linearalgebra.hpp"
#include "paramset.hpp"

enum BackgroundType{
	BACKTYPE_COLORS
};

enum BackgroundMapping{
	BACKMAPPING_SCREEN
};

class Background{

public:
	RgbColor<unsigned char> bl, br, tl, tr;
	BackgroundType type;
	BackgroundMapping mapping;
	Background(ParamSet ps);
	RgbColor<unsigned char> sample(float, float);
};




#endif