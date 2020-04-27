#pragma once
#include<string>
#include "VBO.h"
#include "TileData.h"
#include "Tile.h"
#include <vector>
#include "glm/glm.hpp"
#include <set>
#include "Camera.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <filesystem>
class World;
class Chunk
{
public:
	const static int SIZE = 16;
	const static int SIZE_Y = 256;

	const static int NUM_TILES = SIZE * SIZE_Y * SIZE;
	
	Chunk() = default;
	~Chunk() = default;
	Chunk(Chunk&& chunk) noexcept : x(std::move(chunk.x)), y(std::move(chunk.y)), z(std::move(chunk.z)), world(std::move(chunk.world)),
	pos(std::move(chunk.pos)), generated(std::move(chunk.generated)), needsToSave(std::move(chunk.needsToSave)),
	loadValue(std::move(chunk.loadValue)), changed(std::move(chunk.changed)), needsToRebuild(std::move(chunk.needsToRebuild)),
	triedToLoad(std::move(chunk.triedToLoad)), savefile(std::move(chunk.savefile)), tiles(std::move(chunk.tiles)),
	mesh(std::move(chunk.mesh)){
		
	}
	Chunk& operator=(Chunk&& chunk) {
		x = std::move(chunk.x);
		y = std::move(chunk.y);
		z = std::move(chunk.z);
		world = std::move(chunk.world);
		pos = std::move(chunk.pos);
		generated = std::move(chunk.generated);
		needsToSave = std::move(chunk.needsToSave);
		loadValue = std::move(chunk.loadValue);
		changed = std::move(chunk.changed);
		needsToRebuild = std::move(chunk.needsToRebuild);
		triedToLoad = std::move(chunk.triedToLoad);
		savefile = std::move(chunk.savefile);
		tiles = std::move(chunk.tiles);
		mesh = std::move(chunk.mesh);

		return *this;
	}

	World* world;
	glm::ivec3 pos;

	int voxels = 0;

	bool generated = false;

	std::vector<TileData> tiles;

	VBO mesh;

	bool needsToSave = false;

	float loadValue = 1.0f;

	bool changed = false;

	bool needsToRebuild = false;
	bool triedToLoad = false;

	std::string savefile = "";

	void init(int x, int y, int z, World* world);

	int getX();
	int getY();
	int getZ();
	void setPos(int x, int y, int z);
	void setWorld(World* world);

	void tick();
	void render();

	void dispose();

	Tile* getLocalTile(int x, int y, int z);
	TileData* getTileData(int x, int y, int z, bool modifying);
	void setTileData(int x, int y, int z, TileData data);
	void setLocalTile(int x, int y, int z, Tile* tile);
	void markForRerender();
	void markForSave();
	bool load();
	void save();
	bool canTick();
	bool isActive();
	bool isWithinViewingRange();
	bool canRender();
	glm::ivec3 getWorldPos();
	bool isEmpty();
	bool isLocalTileNotFull(int x, int y, int z);
	void testForActivation();

private:
	int x, y, z;
};

