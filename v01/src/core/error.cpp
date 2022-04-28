#include <iostream>
#include "error.h"

void RT3_ERROR (const std::string &msg) {
	std::cerr << "Ei man, se liga, deu erro. Aqui: " << msg << std::endl;
	std::exit(EXIT_FAILURE);
}

void RT3_WARNING (const std::string &msg) {
	std::cerr << "Ei manito, se liga, deu warning. Aqui: " << msg << std::endl;
}