#include "Tiles.h"

std::unordered_map<int, Tile*> Tiles::REGISTRY;

Tile Tiles::AIR;
Tile Tiles::DIRT;
Tile Tiles::GRASS;
Tile Tiles::STONE;
Tile Tiles::PURPLE_GRASS;
Tile Tiles::LOG;
Tile Tiles::LEAVES;

Tile* Tiles::getTile(int ID) {
	Tile* t = REGISTRY[ID];
	if (t != nullptr) return t;
	return &Tiles::AIR;
}

void Tiles::loadTiles() {
	AIR = Tile("Inignoto", "air");
	DIRT = Tile("Inignoto", "dirt");
	GRASS = Tile("Inignoto", "grass");
	STONE = Tile("Inignoto", "stone");
	PURPLE_GRASS = Tile("Inignoto", "purple_grass");
	LOG = Tile("Inignoto", "log");

	AIR.setFullCube(false)->setRayTraceType(TileRayTraceType::GAS)->setBlocksMovement(false)->setReplaceable();
	DIRT.setHardness(1.0f);
	GRASS.setHardness(1.5f);
	STONE.setHardness(3.0f);
	PURPLE_GRASS.setHardness(GRASS.getHardness());
	LOG.setHardness(2.5f);
	LEAVES.setHardness(0.2f);

	REGISTRY = {
		{0, &AIR},
		{1, &DIRT},
		{2, &GRASS},
		{3, &STONE},
		{4, &PURPLE_GRASS},
		{5, &LOG}
	};
}