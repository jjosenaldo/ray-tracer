#include <iostream>
#include <memory>
#include <string>

#include "parser.hpp"

using std::cout;
using std::endl;
using std::make_unique;
using std::string;

void parseScene(const char* input, unique_ptr<Camera>& camera, unique_ptr<Film>& film){
	TiXmlDocument doc(input);
	
	if(doc.LoadFile()){
		auto rt3 = doc.RootElement();
		
		for (auto child = rt3->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
			string tag = child->ValueStr();

			if(tag == "camera"){ 
				camera = parseCamera(child);
			} 

			else if(tag == "film"){
				film = parseFilm(child);
			}
			
		}

	} else cout << "ERROR: couldn't load file " << input << endl;
}

unique_ptr<Film> parseFilm(const TiXmlElement* camera){
	ParamSet psFilm;
	int xRes, yRes;
	string outFileName, imgType;

	if(camera->QueryIntAttribute("x_res", &xRes) == TIXML_SUCCESS){
		auto xResArr = make_unique<int[]>(1);
		xResArr[0] = xRes;
		psFilm.add<int>("xRes", move(xResArr));
	}

	if(camera->QueryIntAttribute("y_res", &yRes) == TIXML_SUCCESS){
		auto yResArr = make_unique<int[]>(1);
		yResArr[0] = yRes;
		psFilm.add<int>("yRes", move(yResArr));
	}

	if(camera->QueryStringAttribute("filename", &outFileName) == TIXML_SUCCESS){
		auto filenameArr = make_unique<string[]>(1);
		filenameArr[0] = outFileName;
		psFilm.add<string>("filename", move(filenameArr));
	}

	if(camera->QueryStringAttribute("type", &imgType) == TIXML_SUCCESS){
		auto imgTypeArr = make_unique<string[]>(1);
		imgTypeArr[0] = imgType;
		psFilm.add<string>("imgType", move(imgTypeArr));
	}

	return make_unique<Film>(psFilm);
}

unique_ptr<Camera> parseCamera(const TiXmlElement* camera){
	ParamSet ps;

	string type;
	if(camera->QueryStringAttribute("type", &type) == TIXML_SUCCESS){
		auto arr_type = std::make_unique<CameraType[]>(1);

		if(type == "orthographic")
			arr_type[0] = CameraType::CT_ORTHO;

		ps.add<CameraType>("type", move(arr_type));
	}

	return make_unique<Camera>(ps);
}