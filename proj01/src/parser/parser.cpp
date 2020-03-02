#include <iostream>
#include <memory>
#include <string>

#include "parser.hpp"

using std::cout;
using std::endl;
using std::make_unique;
using std::string;

void parseScene(const char* input, unique_ptr<Camera>& camera, unique_ptr<Film>& film, unique_ptr<Background>& background){
	TiXmlDocument doc(input);
	
	if(doc.LoadFile()){
		auto rt3 = doc.RootElement();
		
		for (auto child = rt3->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
			string tag = child->ValueStr();

			if(tag == "camera")
				camera = parseCamera(child);

			else if(tag == "film")
				film = parseFilm(child);

			else if(tag == "world")
				parseWorld(child, background);
			
		}

	} else cout << "ERROR: couldn't load file " << input << endl;
}

void parseWorld(const TiXmlElement* world, unique_ptr<Background>& background){
	for (auto child = world->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
		string tag = child->ValueStr();

		if(tag == "background")
			background = parseBackground(child);		
	}
}


// TODO: the other 3 corners of the screen
unique_ptr<Background> parseBackground(const TiXmlElement* background){
	ParamSet psBack;
	string type, mapping, bl;
	char r,g,b;

	if(background->QueryStringAttribute("type", &type) == TIXML_SUCCESS){
		auto typeArr = make_unique<string[]>(1);
		typeArr[0] = type;
		psBack.add<string>("type", move(typeArr));
	}

	if(background->QueryStringAttribute("mapping", &mapping) == TIXML_SUCCESS){
		auto mappingArr = make_unique<string[]>(1);
		mappingArr[0] = mapping;
		psBack.add<string>("mapping", move(mappingArr));
	}

	if(background->QueryStringAttribute("bl", &bl) == TIXML_SUCCESS){
		stringstream blStream(bl);
		blStream >> r >> g >> b;
		auto blArr = make_unique<char[]>(3);
		blArr[0] = r;
		blArr[1] = g;
		blArr[2] = b;
		psBack.add<int>("bl", move(blArr));
	}	

	return make_unique<Background>(psBack);
}

unique_ptr<Film> parseFilm(const TiXmlElement* film){
	ParamSet psFilm;
	int xRes, yRes;
	string outFileName, imgType, type;

	if(film->QueryIntAttribute("x_res", &xRes) == TIXML_SUCCESS){
		auto xResArr = make_unique<int[]>(1);
		xResArr[0] = xRes;
		psFilm.add<int>("xRes", move(xResArr));
	}

	if(film->QueryIntAttribute("y_res", &yRes) == TIXML_SUCCESS){
		auto yResArr = make_unique<int[]>(1);
		yResArr[0] = yRes;
		psFilm.add<int>("yRes", move(yResArr));
	}

	if(film->QueryStringAttribute("filename", &outFileName) == TIXML_SUCCESS){
		auto filenameArr = make_unique<string[]>(1);
		filenameArr[0] = outFileName;
		psFilm.add<string>("filename", move(filenameArr));
	}

	if(film->QueryStringAttribute("img_type", &imgType) == TIXML_SUCCESS){
		auto imgTypeArr = make_unique<string[]>(1);
		imgTypeArr[0] = imgType;
		psFilm.add<string>("imgType", move(imgTypeArr));
	}

	if(film->QueryStringAttribute("type", &type) == TIXML_SUCCESS){
		auto typeArr = make_unique<string[]>(1);
		typeArr[0] = imgType;
		psFilm.add<string>("type", move(typeArr));
	}

	return make_unique<Film>(psFilm);
}

unique_ptr<Camera> parseCamera(const TiXmlElement* camera){
	ParamSet ps;

	string type;
	if(camera->QueryStringAttribute("type", &type) == TIXML_SUCCESS){
		auto arr_type = std::make_unique<string[]>(1);
		ps.add<string>("type", move(arr_type));
	}

	return make_unique<Camera>(ps);
}