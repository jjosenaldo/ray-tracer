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

void parse(const string input, unique_ptr<Camera>& camera, unique_ptr<Scene>& scene){
	TiXmlDocument doc(input);
	
	if(doc.LoadFile()){
		auto rt3 = doc.RootElement();
		
		for (auto child = rt3->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
			string tag = child->ValueStr();

			if(tag == "camera")
				camera = parseCamera(child);

			else if(tag == "film")
				camera->film = parseFilm(child);

			else if(tag == "world")
				scene = parseScene(child);
			
		}

	} else {cout << "ERROR: couldn't load file " << input << endl;exit(0);}
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
	string type, mapping, bl, br, tl, tr, color;
	short r,g,b;

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

		auto blArr = make_unique<unsigned char[]>(3);
		blArr[0] = (unsigned char)r;
		blArr[1] = (unsigned char)g;
		blArr[2] = (unsigned char)b;
		
		psBack.add<unsigned char>("bl", move(blArr), 3);
	}	

	if(background->QueryStringAttribute("br", &br) == TIXML_SUCCESS){
		stringstream brStream(br);
		brStream >> r >> g >> b;

		auto brArr = make_unique<unsigned char[]>(3);
		brArr[0] = (unsigned char)r;
		brArr[1] = (unsigned char)g;
		brArr[2] = (unsigned char)b;
		
		psBack.add<unsigned char>("br", move(brArr), 3);
	}

	if(background->QueryStringAttribute("tl", &tl) == TIXML_SUCCESS){
		stringstream tlStream(tl);
		tlStream >> r >> g >> b;

		auto tlArr = make_unique<unsigned char[]>(3);
		tlArr[0] = (unsigned char)r;
		tlArr[1] = (unsigned char)g;
		tlArr[2] = (unsigned char)b;
		
		psBack.add<unsigned char>("tl", move(tlArr), 3);
	}

	if(background->QueryStringAttribute("tr", &tr) == TIXML_SUCCESS){
		stringstream trStream(tr);
		trStream >> r >> g >> b;

		auto trArr = make_unique<unsigned char[]>(3);
		trArr[0] = (unsigned char)r;
		trArr[1] = (unsigned char)g;
		trArr[2] = (unsigned char)b;
		
		psBack.add<unsigned char>("tr", move(trArr), 3);
	}

	if(background->QueryStringAttribute("color", &color) == TIXML_SUCCESS){
		stringstream colorStream(color);
		colorStream >> r >> g >> b;

		auto colorArr = make_unique<unsigned char[]>(3);
		colorArr[0] = (unsigned char)r;
		colorArr[1] = (unsigned char)g;
		colorArr[2] = (unsigned char)b;
		
		psBack.add<unsigned char>("color", move(colorArr), 3);
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