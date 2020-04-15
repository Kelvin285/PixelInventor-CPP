#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <functional>

#include "Inignoto.h"

int main() {
	Inignoto inignoto;

	try {
		inignoto.run();
	}
	catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}