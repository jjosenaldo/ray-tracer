#include "background.hpp"

BackgroundType backgroundType(string type){
	if(type == "colors") return BACKTYPE_COLORS;

	return BACKTYPE_COLORS;	
}

backgroundMapping backgroundMapping(string mapping){
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
	
}