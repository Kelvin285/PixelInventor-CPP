#include "FileManager.h"
#include <fstream>
namespace PixelInventor {
	std::string FileManager::read(const char* file) {
		std::ifstream f(file);
		std::string temp;
		std::string result;
		while (std::getline(f, temp)) {
			result += temp + "\n";
		}
		return result;
	}
}