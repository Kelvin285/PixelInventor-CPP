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
#include <iostream>
#include "SeededRandom.h"
#include "Camera.h"
#include "ChunkBuilder.h"
#include "Settings.h"
#include "MathHelper.h"
#include "Tiles.h"
#include <set>
#include <map>
#include <iterator>
#include <mutex>
#include <future>
#include "VBO.h"

class World
{
public:
	struct ActiveChunkStorage {
		bool active;
		Chunk* chunk;
	};
	struct ChunkStorage {
		glm::vec3 position;
		Chunk chunk;
		ChunkStorage() = default;
		ChunkStorage(ChunkStorage&& m1) noexcept : position(std::move(m1.position)), chunk(std::move(m1.chunk)) {

		}
		ChunkStorage& operator=(ChunkStorage&& m1) {
			position = std::move(m1.position);
			chunk = std::move(m1.chunk);
			return *this;
		}
	};

	static std::set<Chunk*> saveQueue;
	//std::vector<Entity> entities;

	bool rebuild = false;

	SeededRandom random;

	

	void init(std::string worldName, long s);

	std::string getPosition(int x, int y, int z) {
		std::string s;
		s += x + ", " + y;
		s += ", " + z;
		return s;
	}

	Chunk* getChunk(int x, int y, int z);

	void removeChunk(int x, int y, int z);

	void addChunk(int x, int y, int z);

	void saveChunks();
	void buildChunks();
	void updateChunkManager();

	void tickChunks();
	void tick();

	void render();

	void renderChunks();

	void renderTileHover();

	void dispose();

	glm::vec3 getSkyColor();

	long getSeed();

	WorldSaver* getWorldSaver();

	void setSeed(long seed);

	RayTraceResult rayTraceTiles(glm::vec3 start, glm::vec3 end, TileRayTraceType type);

	Tile* getTile(TilePos pos);
	TileData* getTileData(TilePos pos, bool modifying);

	bool setTileData(TilePos pos, TileData data);

	Chunk* getChunkAt(TilePos pos);

	bool setTile(TilePos pos, Tile* tile);

	bool setTile(int x, int y, int z, Tile* tile);

	void mineTile(TilePos pos, float strength);
	
	ChunkGenerator* getChunkGenerator();

private:
	std::mutex mutex;
	ChunkGenerator generator;
	long seed;
	
	WorldSaver worldSaver;

	std::vector<ChunkStorage> chunks;
	
	std::vector<ActiveChunkStorage> loadedChunks;

	std::set<Chunk*> rendering;
	
	glm::vec3 cp = glm::vec3(0.0f);

	int mx = 0, my = 0, mz = 0;

	bool setTileData(int x1, int y1, int z1, TileData data);

	bool adding = false;

};

