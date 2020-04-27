#include "World.h"
#include "Inignoto.h"


std::set<Chunk*> World::saveQueue;

void World::init(std::string worldName, long s) {
	worldSaver = WorldSaver(worldName, this, s);
	random = SeededRandom(seed);
	generator = ChunkGenerator(this, seed);

	this->seed = s;

	//pseudochunk.init(0, 0, 0, this);
	//generator.generateChunk(&pseudochunk, true);
	//pseudochunk.mesh = ChunkBuilder::buildChunk(&pseudochunk);
	//Inignoto::game->addVBO(&pseudochunk.mesh);
	addChunk(0, 0, 0);
	std::cout << "Chunk memory location: " << &chunks[0].chunk.mesh << ", x: " << chunks[0].chunk.getX() << std::endl;
	addChunk(1, 0, 0);
	std::cout << "New chunk memory location: " << &chunks[0].chunk.mesh << ", x: " << chunks[0].chunk.getX() << std::endl;
}

Chunk* World::getChunk(int x, int y, int z) {
	for (size_t i = 0; i < chunks.size(); i++) {
		if (chunks[i].position == glm::vec3(x, y, z)) {
			return &chunks[i].chunk;
		}
	}
	return nullptr;
}

void World::removeChunk(int x, int y, int z) {
	for (size_t i = 0; i < chunks.size(); i++) {
		if (chunks[i].position == glm::vec3(x, y, z)) {
			chunks[i].chunk.dispose();
			chunks.erase(chunks.begin() + i);
			break;
		}
	}
}

void World::addChunk(int x, int y, int z) {
	bool contains = false;
	for (size_t i = 0; i < loadedChunks.size(); i++) {
		if (glm::vec3(x, y, z) == glm::vec3(loadedChunks[i].chunk->getX(), loadedChunks[i].chunk->getY(), loadedChunks[i].chunk->getZ())) {
			loadedChunks[i].active = true;
			contains = true;
			break;
		}
	}
	
	if (getChunk(x, y, z) != nullptr) {
		return;
	}
	std::cout << "gen" << std::endl;
	
	ChunkStorage storage;
	storage.position = glm::vec3(x, y, z);
	storage.chunk.init(x, y, z, this);
	chunks.push_back(std::move(storage));

}

void World::saveChunks() {
	if (!saveQueue.empty())
	for (auto at : saveQueue) {
		at->save();
	}
	saveQueue.clear();
}

void World::buildChunks() {
	if (!adding) return;
	int cx = (int)floor(Camera::position.x / Chunk::SIZE);
	int cy = (int)floor(Camera::position.y / Chunk::SIZE_Y);
	int cz = (int)floor(Camera::position.z / Chunk::SIZE);
	cp.x = cx;
	cp.y = cy;
	cp.z = cz;
	double distance = 999999;
	Chunk* closest = nullptr;
	if (!chunks.empty())
	{
		for (size_t i = 0; i < chunks.size(); i++)
		{
			ChunkStorage* storage = &chunks[i];
			double dist = glm::distance(cp, storage->position);
			if (dist < distance)
			if (storage->chunk.generated == false) {
				distance = dist;
				closest = &storage->chunk;
			}
		}
	}

	if (closest != nullptr) {
		generator.generateChunk(closest, true);

		closest->mesh = ChunkBuilder::buildChunk(closest);
		closest->generated = true;
		closest->markForRerender();
	}
}

void World::updateChunkManager() {
	if (!adding) return;
	for (size_t i = 0; i < loadedChunks.size(); i++) {
		if (loadedChunks[i].active == false) {
			Inignoto::game->removeVBO(&loadedChunks[i].chunk->mesh);
		}
	}
	
	loadedChunks.clear();

	for (size_t i = 0; i < chunks.size(); i++) {
		ActiveChunkStorage storage = { false, &chunks[i].chunk };
		loadedChunks.push_back(storage);
	}

	mx = (int)floor(Camera::position.x / Chunk::SIZE);
	my = (int)floor(Camera::position.y / Chunk::SIZE_Y);
	mz = (int)floor(Camera::position.z / Chunk::SIZE);

	
	for (int x = -Settings::VIEW_DISTANCE / 2; x < Settings::VIEW_DISTANCE / 2; x++) {
		for (int z = -Settings::VIEW_DISTANCE / 2; z < Settings::VIEW_DISTANCE / 2; z++) {
			for (int y = -Settings::VERTICAL_VIEW_DISTANCE / 2; y < Settings::VERTICAL_VIEW_DISTANCE / 2; y++) {
				addChunk(x + mx, y + my, z + mz);
			}
		}
	}
	adding = false;
}

void World::tickChunks() {
	for (size_t i = 0; i < chunks.size(); i++) {
		chunks[i].chunk.tick();
	}
}

void World::tick() {
	//TODO: tick entities
}

void World::render() {
	//TODO: update fog
	//TODO: render entities
}

void World::renderChunks() {
	if (adding) return;
	std::cout << chunks.size() << std::endl;
	for (size_t i = 0; i < chunks.size(); i++) {
		chunks[i].chunk.render();
	}
	renderTileHover();
	adding = true;
}

void World::renderTileHover() {
	//TODO: render tile hover
}

void World::dispose() {
	worldSaver.saveWorld();
	//dispose of entities
	for (size_t i = 0; i < chunks.size(); i++) {
		chunks[i].chunk.dispose();
	}
	for (size_t i = 0; i < chunks.size(); i++) {
		chunks[i].chunk.dispose();
	}
}

glm::vec3 World::getSkyColor() {
	return glm::vec3(91.0f / 255.0f, 198.0f / 255.0f, 208.0f / 255.0f);
}

long World::getSeed() {
	return this->seed;
}

void World::setSeed(long seed) {
	this->seed = seed;
}

bool World::setTileData(TilePos pos, TileData data) {
	return setTileData(pos.x, pos.y, pos.z, data);
}

WorldSaver* World::getWorldSaver() {
	return &this->worldSaver;
}

ChunkGenerator* World::getChunkGenerator() {
	return &this->generator;
}

RayTraceResult World::rayTraceTiles(glm::vec3 start, glm::vec3 end, TileRayTraceType type) {
	TilePos pos(start.x, start.y, start.z);

	float length = glm::distance(end, start);

	float inc = 0.001f;
	for (float i = 0; i < length; i += inc) {
		glm::vec3 n(lerp(start, end, i / length));
		pos.setPosition(n.x, n.y, n.z);
		Tile* tile = getTile(pos);

		if (tile != nullptr) {
			if (tile->isVisible()) {
				if (tile->getRayTraceType() == type) {
					return RayTraceResult(RayTraceResult::RayTraceType::TILE, pos, lerp(start, end, (i - inc) / length));
				}
			}
		}
	}
	return RayTraceResult(RayTraceResult::RayTraceType::EMPTY, pos, end);
}

Tile* World::getTile(TilePos pos) {
	int mx = (int)floor((float)pos.x / Chunk::SIZE);
	int my = (int)floor((float)pos.y / Chunk::SIZE_Y);
	int mz = (int)floor((float)pos.z / Chunk::SIZE);
	Chunk* chunk = getChunk(mx, my, mz);
	int x = pos.x - mx * Chunk::SIZE;
	int y = pos.y - my * Chunk::SIZE_Y;
	int z = pos.z - mz * Chunk::SIZE;
	
	if (chunk == nullptr) return &Tiles::AIR;

	return chunk->getLocalTile(x, y, z);
}

TileData* World::getTileData(TilePos pos, bool modifying) {
	int mx = (int)floor((float)pos.x / Chunk::SIZE);
	int my = (int)floor((float)pos.y / Chunk::SIZE_Y);
	int mz = (int)floor((float)pos.z / Chunk::SIZE);
	Chunk* chunk = getChunk(mx, my, mz);
	int x = pos.x - mx * Chunk::SIZE;
	int y = pos.y - my * Chunk::SIZE_Y;
	int z = pos.z - mz * Chunk::SIZE;
	
	if (chunk == nullptr) return new TileData(Tiles::AIR.getID());
	return chunk->getTileData(x, y, z, modifying);
}

bool World::setTileData(int x1, int y1, int z1, TileData data) {
	int mx = (int)floor((float)x1 / Chunk::SIZE);
	int my = (int)floor((float)y1 / Chunk::SIZE_Y);
	int mz = (int)floor((float)z1 / Chunk::SIZE);
	Chunk* chunk = getChunk(mx, my, mz);
	int x = x1 - mx * Chunk::SIZE;
	int y = y1 - my * Chunk::SIZE_Y;
	int z = z1 - mz * Chunk::SIZE;

	if (chunk == nullptr) return false;
	chunk->setTileData(x, y, z, data);
	return true;
}

Chunk* World::getChunkAt(TilePos pos) {
	int mx = (int)floor((float)pos.x / Chunk::SIZE);
	int my = (int)floor((float)pos.y / Chunk::SIZE_Y);
	int mz = (int)floor((float)pos.z / Chunk::SIZE);
	
	return getChunk(mx, my, mz);
}

bool World::setTile(TilePos pos, Tile* tile) {
	return setTile(pos.x, pos.y, pos.z, tile);
}

bool World::setTile(int x1, int y1, int z1, Tile* tile) {
	int mx = (int)floor((float)x1 / Chunk::SIZE);
	int my = (int)floor((float)y1 / Chunk::SIZE_Y);
	int mz = (int)floor((float)z1 / Chunk::SIZE);
	Chunk* chunk = getChunk(mx, my, mz);
	int x = x1 - mx * Chunk::SIZE;
	int y = y1 - my * Chunk::SIZE_Y;
	int z = z1 - mz * Chunk::SIZE;

	if (chunk != nullptr) {
		chunk->setLocalTile(x, y, z, tile);
		chunk->markForRerender();
		chunk->markForSave();
		return true;
	}
	return false;
}

void World::mineTile(TilePos pos, float strength) {
	int mx = (int)floor((float)pos.x / Chunk::SIZE);
	int my = (int)floor((float)pos.y / Chunk::SIZE_Y);
	int mz = (int)floor((float)pos.z / Chunk::SIZE);
	Chunk* chunk = getChunk(mx, my, mz);
	int x = pos.x - mx * Chunk::SIZE;
	int y = pos.y - my * Chunk::SIZE_Y;
	int z = pos.z - mz * Chunk::SIZE;
	if (chunk != nullptr) {
		TileData* data = chunk->getTileData(x, y, z, false);
		data->setMiningTime(data->getMiningTime() + strength / Tiles::getTile(data->getTile())->getHardness());
		int current = (int)(data -> getMiningTime() / 20.0);
		int last = (int)(data->getLastMiningTime() / 20.0);
		if (data->getMiningTime() > 100.0) {
			data->setMiningTime(0.0);
			chunk->setLocalTile(x, y, z, &Tiles::AIR);
			chunk->markForRerender();
			chunk->markForSave();
		}
		else {
			if (current != last) {
				chunk->markForRerender();
			}
		}
	}
}