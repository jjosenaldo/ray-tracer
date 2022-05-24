#include <iostream>
#include "error.h"

void RT3_ERROR (const std::string &msg) {
	std::cerr << "ERROR: " << msg << std::endl;
	std::exit(EXIT_FAILURE);
}

void RT3_WARNING (const std::string &msg) {
	std::cerr << "WARNING: " << msg << std::endl;
}