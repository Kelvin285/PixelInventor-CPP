#pragma once
#include <map>
#include <glm/glm.hpp>
#include "Chunk.h"
namespace PixelInventor {
	class World {
	public:
		World();
		~World();

		void update();
		void render();

		Chunk getChunk(glm::vec2 pos);
		bool doesChunkExist(glm::vec2 pos);

		std::map<glm::vec2, Chunk> getChunks();
	private:
		std::map<glm::vec2, Chunk> chunks;
	};
}