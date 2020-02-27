#ifndef PARSER_HPP
#define PARSER_HPP

#include "camera.hpp"
#include "tinyxml.h"

void parseScene(const char*, unique_ptr<Camera>& );
unique_ptr<Camera> parseCamera(const TiXmlElement *);
void parseFilm(const TiXmlElement *);

#endif