#include <iostream>
#include <memory>
#include <string>

#include "parser.hpp"

using std::cout;
using std::endl;
using std::make_unique;
using std::string;

void parseScene(const char* input, unique_ptr<Camera>& camera){
	TiXmlDocument doc(input);
	
	if(doc.LoadFile()){
		auto rt3 = doc.RootElement();
		
		for (auto child = rt3->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
			string tag = child->ValueStr();

			if(tag == "camera"){ 
				camera = parseCamera(child);
			} 

			else if(tag == "film"){

			}
			
		}

	} else cout << "ERROR: couldn't load file " << input << endl;
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