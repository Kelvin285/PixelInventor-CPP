#include "ChunkGenerator.h"
#include "World.h"
#include "Chunk.h"
ChunkGenerator::ChunkGenerator(World* world, long seed) {
	if (world != nullptr) {
		noise.SetSeed(seed);
		this->world = world;
		this->random = &world->random;
	}
}

void ChunkGenerator::generateChunk(Chunk* chunk, bool structures) {
	chunk->tiles.clear();
	chunk->tiles.resize(Chunk::SIZE * Chunk::SIZE_Y * Chunk::SIZE);
	if (chunk->load()) return;
	for (int x = 0; x < Chunk::SIZE; x++) {
		for (int y = 0; y < Chunk::SIZE_Y; y++) {
			for (int z = 0; z < Chunk::SIZE; z++) {
				chunk->setLocalTile(x, y, z, &Tiles::AIR);
			}
		}
	}
	int nx = chunk->getX() * Chunk::SIZE;
	int ny = chunk->getY() * Chunk::SIZE;
	int nz = chunk->getZ() * Chunk::SIZE;
	for (int x = 0; x < Chunk::SIZE; x++) {
		for (int z = 0; z < Chunk::SIZE; z++) {
			int X = nx + x;
			int Z = nz + z;
			int height = (int)getHeight(X, Z);
			Tile* topTile = getTopTile(X, Z);
			for (int y = 0; y < Chunk::SIZE_Y; y++) {
				int Y = ny + y;

				if (Y == height) {
					chunk->setLocalTile(x, y, z, topTile);
				}
				if (Y < height) {
					chunk->setLocalTile(x, y, z, &Tiles::DIRT);
					//add tree structure to chunk?
				}
			}
		}
	}
	chunk->markForRerender();
}

float ChunkGenerator::getHeight(float x, float z) {
	float height = noise.GetSimplexFractal(x * 2, 0, z * 2) * 24;
	float mountain = noise.GetSimplex(x / 500.0f, 0.0f, z / 500.0f) * 512;

	return height + 64 + mountain;
}

Tile* ChunkGenerator::getTopTile(float x, float z) {
	double purple = noise.GetSimplex(x, 0, z);
	Tile* topTile = &Tiles::GRASS;
	if (purple > 0) {
		topTile = &Tiles::PURPLE_GRASS;
	}
	return topTile;
}