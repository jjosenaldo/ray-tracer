#include "background.hpp"
#include <iostream>

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
	const char* bl = ps.find_array<char>("bl", size); 
	const char* br = ps.find_array<char>("br", size); 
	const char* tl = ps.find_array<char>("tl", size); 
	const char* tr = ps.find_array<char>("tr", size); 

	std::cout << +tl[0] << " " << +(tl[1]) << " " << +tl[2] << "end\n";

	if(bl != nullptr) this->bl = {bl[0], bl[1], bl[2]};
	else this->bl = {0,0,0};

	if(tl != nullptr) this->tl = {tl[0], tl[1], tl[2]};
	else this->tl = {0,0,0};

	if(tr != nullptr) this->tr = {tr[0], tr[1], tr[2]};
	else this->tr = {0,0,0};

	if(br != nullptr) this->br = {br[0], br[1], br[2]};
	else this->br = {0,0,0};
}