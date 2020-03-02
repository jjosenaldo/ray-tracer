#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "color.hpp"
#include "paramset.hpp"

enum BackgroundType{
	BACKTYPE_COLORS
};

enum BackgroundMapping{
	BACKMAPPING_SCREEN
};

class Background{

public:
	RgbColor bl, br, tl, tr;
	BackgroundType type;
	BackgroundMapping mapping;
	Background(BackgroundType type, BackgroundMapping mapping);
	Background(ParamSet ps);
	RgbColor sample(float, float);
};




#endif