#include <algorithm>
#include <cmath>

#include "background.hpp"
#include "linearalgebra.hpp"

using std::max;
using std::min;

BackgroundType backgroundType(string type){
	if(type == "colors") return BACKTYPE_COLORS;

	return BACKTYPE_COLORS;	
}

BackgroundMapping backgroundMapping(string mapping){
	if(mapping == "screen") return BACKMAPPING_SCREEN;

	return BACKMAPPING_SCREEN;
}

Background::Background(BackgroundType type, BackgroundMapping mapping){
	this->type = type;
	this->mapping = mapping;
}

Background::Background(ParamSet ps) : Background(
	backgroundType(ps.find_one<string>("type", "colors")), 
	backgroundMapping(ps.find_one<string>("mapping", "screen"))) {
	size_t size;
	const unsigned char* bl = ps.find_array<unsigned char>("bl", size); 
	const unsigned char* br = ps.find_array<unsigned char>("br", size); 
	const unsigned char* tl = ps.find_array<unsigned char>("tl", size); 
	const unsigned char* tr = ps.find_array<unsigned char>("tr", size); 

	if(bl != nullptr) this->bl = {bl[0], bl[1], bl[2]};
	else this->bl = {0,0,0};

	if(tl != nullptr) this->tl = {tl[0], tl[1], tl[2]};
	else this->tl = {0,0,0};

	if(tr != nullptr) this->tr = {tr[0], tr[1], tr[2]};
	else this->tr = {0,0,0};

	if(br != nullptr) this->br = {br[0], br[1], br[2]};
	else this->br = {0,0,0};
}

RgbColor Background::sample(float x, float y){
	float floatR = bilinearInterpolation(x, y, (float)bl.r, (float)tl.r, (float)tr.r, (float)br.r);
	float floatG = bilinearInterpolation(x, y, (float)bl.g, (float)tl.g, (float)tr.g, (float)br.g);
	float floatB = bilinearInterpolation(x, y, (float)bl.b, (float)tl.b, (float)tr.b, (float)br.b);
	unsigned char r = max(min((int)round(floatR), 255), 0);
	unsigned char g = max(min((int)round(floatG), 255), 0);
	unsigned char b = max(min((int)round(floatB), 255), 0);
	return {r,g,b};
}

