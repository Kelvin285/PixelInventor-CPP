#pragma once
#include "Tile.h"
#include "ArrayList.h"
namespace PixelInventor {
	class Tiles {
	public:
		static ArrayList<Tile> tiles;

		static Tile AIR;
		static GroundTile DIRT;
		static GroundTile GRASS;
		static GroundTile PURPLE_GRASS;

		static void run();
	};
}