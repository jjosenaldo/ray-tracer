#include <iostream>
#include <string>

#include "parser.hpp"
#include "tinyxml.h"

using std::cout;
using std::endl;
using std::string;

void parse(const char* input){
	TiXmlDocument doc(input);
	
	if(doc.LoadFile()){
		auto rt3 = doc.RootElement();
		
		for (auto child = rt3->FirstChildElement(); child != NULL; child = child->NextSiblingElement()){
			string tag = child->ValueStr();

			if(tag == "camera"){
				cout << "it's a camera\n";
			} else cout << "it's not a camera\n";
		}

	} else cout << "Couldn't load file " << input << endl;
}