#include "World.h"
namespace PixelInventor {

	Chunk chunk;
	World::World() {

	}

	World::~World() {
		
	}

	void World::update() {

	}

	void World::render() {
		chunk.render();
	}
	
	Chunk World::getChunk(int x, int y) {

	}

	bool World::doesChunkExist(int x, int y) {

	}

	std::map<glm::vec2, Chunk> World::getChunks() {

	}
}