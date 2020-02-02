#pragma once
#include <string>
namespace PixelInventor {
	class FileManager {
	public:
		static std::string read(const char* file);
	};
}