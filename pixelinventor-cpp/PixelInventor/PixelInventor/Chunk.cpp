#include "Chunk.h"
#include "ChunkRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Textures.h"
#include "Shaders.h"
#include <chrono>
#include <ctime>
#include "Constants.h"
#include "Tile.h"
#include "World.h"
#include "Tiles.h"
#include "HashMap.h"
namespace PixelInventor {
	

	Chunk::Chunk(int x, int y, World* world) {
		this->X = x;
		this->Y = y;
		this->world = world;
		for (unsigned int x = 0; x < Chunk::SIZE; x++) {
			for (unsigned int y = 0; y < Chunk::SIZE; y++) {
				if (x % 2 == 0) {
					tiles[x][y] = &Tiles::DIRT;
				}
				else {
					tiles[x][y] = &Tiles::AIR;
				}
			}
		}
	}
	Chunk::~Chunk() {
		for (unsigned int x = 0; x < Chunk::SIZE; x++) {
			for (unsigned int y = 0; y < Chunk::SIZE; y++) {
				delete tiles[x][y];
			}
		}
		delete world;
	}

	void Chunk::markForRerender() {
		this->rerender = true;
	}

	void Chunk::update() {
		for (unsigned int x = 0; x < Chunk::SIZE; x++) {
			for (unsigned int y = 0; y < Chunk::SIZE; y++) {
				Tile* tile = tiles[x][y];
				if (tile != nullptr) {
					tile->update(glm::vec2(x, y), this);
				}
			}
		}
	}

	float positionData[] = {

		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	float colorData[] = {

		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	void Chunk::render() {
		Shaders::DEFAULT.bind();
		ChunkRenderer::renderChunk(this);
	}

	void Chunk::reshape() {

	}
	void Chunk::recalulateNextLights() {

	}
	void Chunk::recalculateLights() {

	}
	glm::vec3 Chunk::getRenderLight(int x, int y) {

	}
	glm::vec3 Chunk::getLight(int x, int y) {

	}
	void Chunk::setLight(int x, int y, glm::vec3 light) {

	}
	float Chunk::getDistortion(int x, int y) {

	}
	void Chunk::setDistortion(int x, int y, float distorted) {

	}
	glm::vec2 Chunk::getState(int x, int y) {

	}
	void Chunk::setState(int x, int y, glm::vec2 state) {

	}
	Tile* Chunk::getTile(int x, int y) {
		int X = 0;
		int Y = 0;
		if (x < 0) {
			x += Chunk::SIZE;
			X = -1;
		}
		if (x > Chunk::SIZE - 1) {
			x -= Chunk::SIZE;
			X = 1;
		}

		if (y < 0) {
			y += Chunk::SIZE;
			Y = -1;
		}
		if (y > Chunk::SIZE - 1) {
			y -= Chunk::SIZE;
			Y = 1;
		}

		if (X != 0 || Y != 0) {
			if (world->doesChunkExist(glm::vec2(getX() + X, getY() + Y))) {
				Chunk* c2 = world->getChunk(glm::vec2(getX() + X, getY() + Y));
				return c2->getTile(x, y);
			}
		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return &Tiles::AIR;
		}
		return tiles[x][y];
	}
	void Chunk::setTile(int x, int y, Tile tile) {
		int X = 0;
		int Y = 0;
		if (x < 0) {
			x += Chunk::SIZE;
			X = -1;
		}
		if (x > Chunk::SIZE - 1) {
			x -= Chunk::SIZE;
			X = 1;
		}

		if (y < 0) {
			y += Chunk::SIZE;
			Y = -1;
		}
		if (y > Chunk::SIZE - 1) {
			y -= Chunk::SIZE;
			Y = 1;
		}

		if (X != 0 || Y != 0) {
			if (world->doesChunkExist(glm::vec2(getX() + X, getY() + Y))) {
				Chunk* c2 = world->getChunk(glm::vec2(getX() + X, getY() + Y));
				c2->setTile(x, y, tile);
				return;
			}
			
		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return;
		}

		tiles[x][y] = &tile;
		distortion[x][y] = tiles[x][y]->getDistortionFactor();
		lights[x][y] = tiles[x][y]->getLightValue();
		reshape();
		markForRerender();
	}
}