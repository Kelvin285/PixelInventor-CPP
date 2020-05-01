#pragma once
#include "FastNoise.h"
#include "SeededRandom.h"
#include "Tile.h"
#include "Tiles.h"
class World;
class Chunk;
class ChunkGenerator
{
public:
	
	FastNoise noise;
	SeededRandom* random;
	World* world;

	ChunkGenerator(World* world = nullptr, long s = 0);

	void generateChunk(Chunk& chunk, bool structures);

	float getHeight(float x, float z);
	Tile* getTopTile(float x, float z);
};

