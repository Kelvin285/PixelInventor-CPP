#pragma once
#include <set>
#include "Chunk.h"
#include "ChunkGenerator.h"
#include "WorldSaver.h"
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <string>
#include "Tile.h"
#include "RayTraceResult.h"
#include "TilePos.h"
#include "TileData.h"

class World
{
public:
	static std::set<Chunk*> saveQueue;
	//std::vector<Entity> entities;
	std::set<Chunk*> unloadedChunks;
	std::set<Chunk*> activeChunks;
	std::set<Chunk*> rendering;

	static Chunk pseudochunk;
	bool rebuild = false;

	World(std::string worldName, long s);

	Chunk* getChunk(int x, int y, int z) {
		return chunks[glm::vec3(x, y, z)];
	}

	void removeChunk(int x, int y, int z) {
		chunks.erase(glm::vec3(x, y, z));
	}

	void addChunk(int x, int y, int z) {
		if (getChunk(x, y, z) == nullptr) {
			chunks.insert({ glm::vec3(x, y, z), new Chunk(x, y, z, this) });
		}
		activeChunks.insert(chunks[glm::vec3(x, y, z)]);
		unloadedChunks.insert(chunks[glm::vec3(x, y, z)]);
	}

	void saveChunks();
	void buildChunks();
	void updateChunkManager();

	void tickChunks();
	void tick();

	void render();

	void renderChunks();

	void renderTileHover();

	void dispose();

	glm::vec3 getSkyColor() {
		return glm::vec3(91.0f / 255.0f, 198.0f / 255.0f, 208.0f / 255.0f);
	}

	long getSeed() {
		return this->seed;
	}

	WorldSaver* getWorldSaver() {
		return &this->worldSaver;
	}

	void setSeed(long seed) {
		this->seed = seed;
	}

	RayTraceResult rayTraceTiles(glm::vec3 start, glm::vec3 end, TileRayTraceType type);

	Tile* getTile(TilePos pos);
	TileData* getTileData(TilePos pos, bool modifying);

	bool setTileData(TilePos pos, TileData data) {
		return setTileData(pos.x, pos.y, pos.z, data);
	}

	Chunk getChunkAt(TilePos pos);

	bool setTile(TilePos pos, Tile* tile);

	bool setTile(int x, int y, int z, Tile* tile);

	void mineTile(TilePos pos, float strength);

	ChunkGenerator getChunkGenerator() {
		return this->generator;
	}

private:
	ChunkGenerator generator;
	long seed;
	
	WorldSaver worldSaver;

	std::unordered_map<glm::vec3, Chunk*> chunks;
	glm::vec3 cp = glm::vec3(0.0f);

	int mx, my, mz;
	bool adding = false;

	bool setTileData(int x1, int y1, int z1, TileData data);
};

