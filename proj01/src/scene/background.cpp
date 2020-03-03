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

Background::Background(ParamSet ps) {
	this->type = backgroundType(ps.find_one<string>("type", "colors"));
	this->mapping = backgroundMapping(ps.find_one<string>("mapping", "screen"));
	this->bl = RgbColor<unsigned char>();
	this->tl = RgbColor<unsigned char>();
	this->tr = RgbColor<unsigned char>();
	this->br = RgbColor<unsigned char>();

	size_t size;
	auto color = ps.find_array<unsigned char>("color", size); 
	if(color != nullptr) {
		this->bl.set(color[0], color[1], color[2]);
		this->br.set(color[0], color[1], color[2]);
		this->tl.set(color[0], color[1], color[2]);
		this->tr.set(color[0], color[1], color[2]);
	}
	
	else{
		auto bl = ps.find_array<unsigned char>("bl", size); 
		auto br = ps.find_array<unsigned char>("br", size); 
		auto tl = ps.find_array<unsigned char>("tl", size); 
		auto tr = ps.find_array<unsigned char>("tr", size); 

		if(bl != nullptr) this->bl.set(bl[0], bl[1], bl[2]);
		if(br != nullptr) this->br.set(br[0], br[1], br[2]);
		if(tl != nullptr) this->tl.set(tl[0], tl[1], tl[2]);
		if(tr != nullptr) this->tr.set(tr[0], tr[1], tr[2]);
	}
}

RgbColor<unsigned char> Background::sample(float x, float y){
	float floatR = bilinearInterpolation(x, y, (float)bl.r(), (float)tl.r(), (float)tr.r(), (float)br.r());
	float floatG = bilinearInterpolation(x, y, (float)bl.g(), (float)tl.g(), (float)tr.g(), (float)br.g());
	float floatB = bilinearInterpolation(x, y, (float)bl.b(), (float)tl.b(), (float)tr.b(), (float)br.b());
	unsigned char r = max(min((int)round(floatR), 255), 0);
	unsigned char g = max(min((int)round(floatG), 255), 0);
	unsigned char b = max(min((int)round(floatB), 255), 0);
	return {r,g,b};
}

