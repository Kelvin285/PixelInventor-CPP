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
	
	bool nullchunk = false;

	Chunk(bool n = false) : nullchunk(n) {
	}

	Chunk(const Chunk& old) noexcept {
		nullchunk = (old.nullchunk);
		world = (old.world);
		pos = (old.pos);
		voxels = (old.voxels);
		generated = (old.generated);
		tiles = (old.tiles);
		mesh = (old.mesh);
		needsToSave = (old.needsToSave);
		loadValue = (old.loadValue);
		changed = (old.changed);
		needsToRebuild = (old.needsToRebuild);
		triedToLoad = (old.triedToLoad);
		savefile = (old.savefile);
		x = (old.x);
		y = (old.y);
		z = (old.z);
	}

	Chunk& operator=(Chunk& old) {
		nullchunk = (old.nullchunk);
		world = (old.world);
		pos = (old.pos);
		voxels = (old.voxels);
		generated = (old.generated);
		tiles = (old.tiles);
		mesh = (old.mesh);
		needsToSave = (old.needsToSave);
		loadValue = (old.loadValue);
		changed = (old.changed);
		needsToRebuild = (old.needsToRebuild);
		triedToLoad = (old.triedToLoad);
		savefile = (old.savefile);
		x = (old.x);
		y = (old.y);
		z = (old.z);
		return *this;
	}

	World* world;
	glm::ivec3 pos;

	int voxels = 0;

	bool generated = false;

	std::vector<TileData> tiles;

	int mesh;

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
	TileData& getTileData(int x, int y, int z, bool modifying);
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

