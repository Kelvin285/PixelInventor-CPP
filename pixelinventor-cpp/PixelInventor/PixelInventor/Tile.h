#pragma once
#include <string>

namespace PixelInventor {
	class Tile {
	public:
		Tile(std::string location);
		~Tile();
		std::string location;
	};
}