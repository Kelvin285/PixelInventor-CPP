#include "Tiles.h"

Tile* Tiles::AIR;
Tile* Tiles::DIRT;
Tile* Tiles::GRASS;
Tile* Tiles::STONE;
Tile* Tiles::PURPLE_GRASS;
Tile* Tiles::LOG;
Tile* Tiles::LEAVES;

void Tiles::loadTiles() {
	AIR = new Tile("Inignoto", "air")->setFullCube(false)->setRayTraceType(TileRayTraceType::GAS)->setBlocksMovement(false)->setReplaceable();
	DIRT = new Tile("Inignoto", "dirt")->setHardness(1.0f);
	GRASS = new Tile("Inignoto", "grass")->setHardness(1.5f);
	STONE = new Tile("Inignoto", "stone")->setHardness(3.0f);
	PURPLE_GRASS = new Tile("Inignoto", "purple_grass")->setHardness(GRASS->getHardness());
	LOG = new Tile("Inignoto", "log")->setHardness(2.5f);
	LEAVES = new Tile("Inignoto", "leaves")->setHardness(0.2f);
}