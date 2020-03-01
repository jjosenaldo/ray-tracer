#ifndef PARSER_HPP
#define PARSER_HPP

#include "camera.hpp"
#include "film.hpp"
#include "tinyxml.h"

void parseScene(const char* input, unique_ptr<Camera>& camera, unique_ptr<Film>& film);
unique_ptr<Camera> parseCamera(const TiXmlElement *);
unique_ptr<Film> parseFilm(const TiXmlElement *);

#endif