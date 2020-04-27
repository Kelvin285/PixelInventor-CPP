#include "Chunk.h"
#include "World.h"
#include "Inignoto.h"
#include "ChunkBuilder.h"
namespace fs = std::filesystem;

void Chunk::init(int x, int y, int z, World* world) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->world = world;

	int X = x * Chunk::SIZE;
	int Y = y * Chunk::SIZE_Y;
	int Z = z * Chunk::SIZE;
	pos = glm::ivec3(X, Y, Z);
	std::cout << x << ", " << y << ", " << z << std::endl;
}

int Chunk::getX() {
	return x;
}

int Chunk::getY() {
	return y;
}

int Chunk::getZ() {
	return z;
}

void Chunk::setPos(int x, int y, int z) {
	int X = x * Chunk::SIZE;
	int Y = y * Chunk::SIZE_Y;
	int Z = z * Chunk::SIZE;
	pos.x = X;
	pos.y = Y;
	pos.z = Z;
	this->x = x;
	this->y = y;
	this->z = z;
}

void Chunk::setWorld(World* world) {
	this->world = world;
}

Tile* Chunk::getLocalTile(int x, int y, int z) {
	if (x >= 0 && y >= 0 && z >= 0 && x < Chunk::SIZE && y < Chunk::SIZE_Y && z < Chunk::SIZE) {
		return Tiles::getTile(tiles[x + y * Chunk::SIZE + z * Chunk::SIZE * Chunk::SIZE_Y].getTile());
	}
	return &Tiles::AIR;
}

TileData* Chunk::getTileData(int x, int y, int z, bool modifying) {
	if (x >= 0 && y >= 0 && z >= 0 && x < Chunk::SIZE && y < Chunk::SIZE_Y && z < Chunk::SIZE) {
		if (modifying) changed = true;
		return &tiles[x + y * Chunk::SIZE + z * Chunk::SIZE * Chunk::SIZE_Y];
	}
	return &TileData(Tiles::AIR.getID());
}

void Chunk::setTileData(int x, int y, int z, TileData data) {
	if (x >= 0 && y >= 0 && z >= 0 && x < Chunk::SIZE && y < Chunk::SIZE_Y && z < Chunk::SIZE) {
		tiles[x + y * Chunk::SIZE + z * Chunk::SIZE * Chunk::SIZE_Y] = data;
	}
}

void Chunk::setLocalTile(int x, int y, int z, Tile* tile)
{
	if (x >= 0 && y >= 0 && z >= 0 && x < Chunk::SIZE && y < Chunk::SIZE_Y && z < Chunk::SIZE) {
		Tile* local = getLocalTile(x, y, z);
		if (tile == &Tiles::AIR && local != &Tiles::AIR) {
			if (voxels > 0) {
				voxels--;
			}
		}
		if (tile != &Tiles::AIR && local == &Tiles::AIR) {
			voxels++;
		}
		tiles[x + y * Chunk::SIZE + z * Chunk::SIZE * Chunk::SIZE_Y].setTile(tile->getID());

	}
}

void Chunk::markForRerender() {
	this->needsToRebuild = true;
}

void Chunk::markForSave() {
	/*
	this->needsToSave = true;
	if (world->saveQueue.count(this) == 0)
		world->saveQueue.insert(this);
	*/
	
}

void Chunk::save() {
	/*
	if (!this->needsToSave) return;
	std::string DIR = "Inignoto/saves/" + world->getWorldSaver()->getWorldName() + "/";
	std::ofstream save(DIR.c_str());
	for (auto at : tiles) {
		save << at.getTile() << std::endl << at.getMiningTime() << std::endl << at.getWaterLevel() << std::endl;
	}
	save.close();
	*/
	
}

bool Chunk::load() {
	/*
	std::string DIR = "Inignoto/saves/" + world->getWorldSaver()->getWorldName() + "/";
	if (!fs::exists(DIR)) return false;

	bool setTile = false;
	std::ifstream load(DIR.c_str());
	for (int i = 0; i < NUM_TILES; i++) {
		int tile;
		int miningTime;
		float waterLevel;
		load >> tile >> miningTime >> waterLevel;
		tiles[i].setMiningTime(miningTime);
		tiles[i].setMiningTime(miningTime);
		tiles[i].setWaterLevel(waterLevel);
	}
	*/
	return false;
}

void Chunk::tick() {

}

void Chunk::render() {
	if (voxels <= 0) return;
	if (needsToRebuild) {
		if (!mesh.created) {
			mesh.createVertexBuffer();
		}
		
		if (mesh.indices.size() > 0) {
			Inignoto::game->addVBO(&mesh);
		}
		needsToRebuild = false;
	}
	if (canRender()) {
		if (loadValue > 0) {
			loadValue -= 0.02f * FPSCounter::getDelta();
		}
		else {
			loadValue = 0;
		}
		mesh.loadValue = loadValue;
		mesh.position = pos;
		mesh.scale = glm::vec3(1.0f);
		
	}
}


void Chunk::dispose() {
	if (this->mesh.created)
	this->mesh.dispose();
	if (needsToSave) this->save();
}

bool Chunk::canTick() {
	if (voxels <= 0) return false;
	int x = getX() * Chunk::SIZE + Chunk::SIZE / 2;
	int z = getZ() * Chunk::SIZE + Chunk::SIZE / 2;
	return glm::distance(Camera::position, glm::vec3(x, 0, z)) <= Chunk::SIZE * Constants::ACTIVE_CHUNK_DISTANCE;
}
bool Chunk::isActive() {
	if (voxels <= 0) return false;
	int x = getX() * Chunk::SIZE + Chunk::SIZE / 2;
	int y = getY() * Chunk::SIZE_Y + Chunk::SIZE_Y / 2;
	int z = getZ() * Chunk::SIZE + Chunk::SIZE / 2;
	return glm::distance(Camera::position, glm::vec3(x, y, z)) < Chunk::SIZE * Chunk::SIZE * 1.5;
}

bool Chunk::isWithinViewingRange() {
	int x = getX() * Chunk::SIZE + Chunk::SIZE / 2;
	int z = getZ() * Chunk::SIZE + Chunk::SIZE / 2;
	return glm::distance(Camera::position, glm::vec3(x, 0, z)) <= Chunk::SIZE * Settings::VIEW_DISTANCE;
}
bool Chunk::canRender() {
	int x = getX() * Chunk::SIZE + Chunk::SIZE / 2;
	int y = getY() * Chunk::SIZE_Y + Chunk::SIZE_Y / 2;
	int z = getZ() * Chunk::SIZE + Chunk::SIZE / 2;
	//check for frustum
	return glm::distance(Camera::position, glm::vec3(x, 0, z)) <= SIZE * Settings::VIEW_DISTANCE || glm::distance(Camera::position * glm::vec3(0, 1, 0), glm::vec3(0, y, 0)) <= SIZE_Y * Settings::VERTICAL_VIEW_DISTANCE;
}
glm::ivec3 Chunk::getWorldPos() {
	return this->pos;
}
bool Chunk::isEmpty() {
	return voxels <= 0;
}
bool Chunk::isLocalTileNotFull(int x, int y, int z) {
	Tile* local = getLocalTile(x, y, z);
	return !local->isFull() || !local->isVisible();
}
void Chunk::testForActivation() {
	if (needsToRebuild) {
		needsToRebuild = false;
		mesh = ChunkBuilder::buildChunk(this);

		if (mesh.created == true) {
			if (mesh.uniformBuffersMemory.size() > 0) {
				Inignoto::game->addVBO(&mesh);
			}
		}
	}
	
	
}