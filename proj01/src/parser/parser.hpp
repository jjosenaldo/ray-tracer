#ifndef PARSER_HPP
#define PARSER_HPP

#include "camera.hpp"
#include "tinyxml.h"

void parseScene(const char*, Camera& );
Camera parseCamera(const TiXmlElement *);
void parseFilm(const TiXmlElement *);

#endif