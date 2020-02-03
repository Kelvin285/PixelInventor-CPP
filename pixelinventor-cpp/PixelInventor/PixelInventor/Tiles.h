#pragma once
#include "Tile.h"
#include "ArrayList.h"
namespace PixelInventor {
	class Tiles {
	public:
		static ArrayList<Tile> tiles;

		static Tile AIR;
		static Tile DIRT;

		static void run();
	};
}