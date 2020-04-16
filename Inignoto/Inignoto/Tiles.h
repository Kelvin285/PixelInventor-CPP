#pragma once
#include "Tile.h"
#include <unordered_map>
#include <string>
class Tiles
{
public:
	static std::unordered_map<std::string, Tile*> REGISTRY;

	static Tile* AIR;
	static Tile* DIRT;
	static Tile* GRASS;
	static Tile* STONE;
	static Tile* PURPLE_GRASS;
	static Tile* LOG;
	static Tile* LEAVES;

	static Tile* getTile(int ID) {
		for (auto at : REGISTRY) {
			if (at.second->getID() == ID) return at.second;
		}
		return Tiles::AIR;
	}

	static void loadTiles();
};

