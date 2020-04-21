#pragma once
#include "Tile.h"
#include <unordered_map>
#include <string>
class Tiles
{
public:
	static std::unordered_map<int, Tile*> REGISTRY;

	static Tile AIR;
	static Tile DIRT;
	static Tile GRASS;
	static Tile STONE;
	static Tile PURPLE_GRASS;
	static Tile LOG;
	static Tile LEAVES;

	static Tile* getTile(int ID);

	static void loadTiles();
};

