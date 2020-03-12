#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include <sstream>

#include "background.hpp"
#include "camera.hpp"
#include "rt3.hpp"
#include "scene.hpp"
#include "film.hpp"
#include "tinyxml.h"

using std::make_unique;
using std::stringstream;

Rt3 parse(const string input);
unique_ptr<Background> parseBackground(const TiXmlElement* background);
ParamSet parseCamera(const TiXmlElement *);
unique_ptr<Film> parseFilm(const TiXmlElement *);
ParamSet parseLookat(const TiXmlElement* lookat);
unique_ptr<Scene> parseScene(const TiXmlElement* world);

template <typename T>
void addItemToParamset(const TiXmlElement* el, const char* tag, int size, string param, ParamSet& ps){
	string val;

	if(el->QueryStringAttribute(tag, &val) == TIXML_SUCCESS ){
		stringstream stream(val);
		auto arr = make_unique<T[]>(size);
		for(int i = 0; i < size; ++i)
			stream >> arr[i];
		ps.add<T>(param, move(arr), size);
	}
}

#endif