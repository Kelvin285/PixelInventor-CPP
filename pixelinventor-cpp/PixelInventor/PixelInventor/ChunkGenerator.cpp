#include "ChunkGenerator.h"
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include "World.h"
#include "Chunk.h"
#include "Tiles.h"
#include "Constants.h"
namespace PixelInventor {
	ChunkGenerator::ChunkGenerator(World* world) {
		this->world = world;
	}
	ChunkGenerator::~ChunkGenerator() {

	}

	void ChunkGenerator::generateChunk(Chunk* chunk) {
		for (int x = 0; x < Chunk::SIZE; x++) {
			for (int y = 0; y < Chunk::SIZE; y++) {
				int X = x + chunk->getX() * Chunk::SIZE;
				int Y = y + chunk->getY() * Chunk::SIZE;
				float base = glm::simplex(glm::vec2(X / 64.0, 0)) * 10.0f;
				float bump = glm::simplex(glm::vec2(X / 64.0f, Y / 32.0f)) * 15.0f;
				float overhang = glm::simplex(glm::vec2(X / 64.0f, Y / 64.0f)) * 15.0f;

				int HEIGHT = (int)(base + bump);

				chunk->setTile(x, y, &Tiles::AIR);
				
				if (Y <= HEIGHT) {
					chunk->setTile(x, y, &Tiles::DIRT);
				}
				if (Y - 1 <= HEIGHT && Y + 1 >= HEIGHT) {
					chunk->setTile(x, y, &Tiles::PURPLE_GRASS);
				}
				if (Y >= Constants::SPACE / Constants::tilesize && overhang > 10) {
					chunk->setTile(x, y, &Tiles::DIRT);
				}
			}
		}
	}
}