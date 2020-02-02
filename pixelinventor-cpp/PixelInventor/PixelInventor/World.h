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

		Chunk getChunk(int x, int y);
		bool doesChunkExist(int x, int y);

		std::map<glm::vec2, Chunk> getChunks();
	private:
		std::map<glm::vec2, Chunk> chunks;
	};
}