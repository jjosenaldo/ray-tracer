#ifndef SCENE_HPP
#define SCENE_HPP

#include "background.hpp"

struct Scene{
	unique_ptr<Background> background;
};


#endif /* SCENE_HPP */