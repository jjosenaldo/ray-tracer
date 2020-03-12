#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "parser.hpp"

using std::cout;
using std::endl;
using std::make_unique;
using std::string;
using std::stringstream;

/* Since there are no template variables, this piece of code is here in the .cpp file */
/* To avoid the "specialization after initiation" error, the implementation of the function
should be done before it is actually used */
template <>
void addItemToParamset<unsigned char>(const TiXmlElement* el, const char* tag, int size, string param, ParamSet& ps){
	string val;

	if(el->QueryStringAttribute(tag, &val) == TIXML_SUCCESS ){
		stringstream stream(val);
		auto arr = make_unique<unsigned char[]>(size);
		short tmp;
		for(int i = 0; i < size; ++i){
			stream >> tmp;
			arr[i] = (unsigned char)tmp;
		}
		ps.add<unsigned char>(param, move(arr), size);
	}
}

Rt3 parse(const string input){
	Rt3 rt3Obj;
	ParamSet psLookat, psCamera;

	TiXmlDocument doc(input);
	
	if(doc.LoadFile()){
		auto rt3Tag = doc.RootElement();
		
		for (auto child = rt3Tag->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
			string tag = child->ValueStr();

			if(tag == "camera")
				psCamera = parseCamera(child);

			if(tag == "lookat"){
				psLookat = parseLookat(child);
			}

			else if(tag == "film")
				rt3Obj.camera->film = parseFilm(child);

			else if(tag == "world")
				rt3Obj.scene = parseScene(child);
			
		}

	} else {cout << "ERROR: couldn't load file " << input << endl;exit(0);}

	rt3Obj.camera->readParamSet(psCamera);
	rt3Obj.camera->readParamSet(psLookat);

	return rt3Obj;
}

ParamSet parseLookat(const TiXmlElement* lookat){
	ParamSet ps;

	addItemToParamset<int>(lookat, "look_from", 3, "lookFrom", ps);
	addItemToParamset<int>(lookat, "look_at", 3, "lookAt", ps);
	addItemToParamset<int>(lookat, "up", 3, "up", ps);

	return ps;
}

unique_ptr<Scene> parseScene(const TiXmlElement* world){
	auto scene = make_unique<Scene>();

	for (auto child = world->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
		string tag = child->ValueStr();

		if(tag == "background")
			scene->background = parseBackground(child);		
	}

	return scene;
}

unique_ptr<Background> parseBackground(const TiXmlElement* background){
	ParamSet psBack;

	addItemToParamset<string>(background, "type", 1, "type", psBack);
	addItemToParamset<string>(background, "mapping", 1, "mapping", psBack);
	addItemToParamset<unsigned char>(background, "bl", 3, "bl", psBack);
	addItemToParamset<unsigned char>(background, "br", 3, "br", psBack);
	addItemToParamset<unsigned char>(background, "tl", 3, "tl", psBack);
	addItemToParamset<unsigned char>(background, "tr", 3, "tr", psBack);
	addItemToParamset<unsigned char>(background, "color", 3, "color", psBack);

	return make_unique<Background>(psBack);
}

unique_ptr<Film> parseFilm(const TiXmlElement* film){
	ParamSet psFilm;
	
	addItemToParamset<int>(film, "x_res", 1, "xRes", psFilm);
	addItemToParamset<int>(film, "y_res", 1, "yRes", psFilm);
	addItemToParamset<string>(film, "filename", 1, "filename", psFilm);
	addItemToParamset<string>(film, "img_type", 1, "imgType", psFilm);
	addItemToParamset<string>(film, "type", 1, "type", psFilm);

	return make_unique<Film>(psFilm);
}

ParamSet parseCamera(const TiXmlElement* camera){
	ParamSet ps;

	addItemToParamset<string>(camera, "type", 1, "type", ps);

	return ps;
}

