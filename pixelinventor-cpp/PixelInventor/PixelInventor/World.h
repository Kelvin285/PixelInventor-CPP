#pragma once
#include <glm/glm.hpp>
#include "Chunk.h"
#include "Camera.h"
#include "ChunkGenerator.h"
#include "Constants.h"
namespace PixelInventor {
	class World {
	public:
		ChunkGenerator chunkGenerator = ChunkGenerator(this);

		World();
		~World();

		void update();
		void render();

		Chunk* getChunk(glm::vec2 pos);
		bool doesChunkExist(glm::vec2 pos);

		void reshapeChunk(glm::vec2 pos);

		void addChunk(glm::vec2 pos);

		glm::vec3 getSkyColor() {
			glm::vec3 skyColor = glm::vec3(64.0 / 255.0, 144.0 / 255.0, 203.0 / 255.0);
			float RY = Camera::Y;
			
			if (RY > Constants::SPACE) {
				float val = (float)((1.0 / 255) * (RY - Constants::SPACE) * 0.1);
				skyColor.r -= val;
				if (skyColor.r < 0) skyColor.r = 0;
				
				skyColor.g -= val;
				if (skyColor.g < 0) skyColor.g = 0;

				skyColor.b -= val;
				if (skyColor.b < 0) skyColor.b = 0;
			}
			return skyColor;
		}
	private:
		void reshapeNextChunk(glm::vec2 pos);
	};
}