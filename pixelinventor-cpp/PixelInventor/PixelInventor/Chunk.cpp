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
#include "MathFunc.h"
namespace PixelInventor {
	

	Chunk::Chunk(int x, int y, World* world) {
		this->X = x;
		this->Y = y;
		this->world = world;
		this->world->chunkGenerator.generateChunk(this);
	}
	Chunk::~Chunk() {
		for (int x = 0; x < Chunk::SIZE; x++) {
			for (int y = 0; y < Chunk::SIZE; y++) {
				delete tiles[x][y];
			}
		}
		delete world;
	}

	void Chunk::markForRerender() {
		this->rerender = true;
	}

	void Chunk::update() {
		for (int x = 0; x < Chunk::SIZE; x++) {
			for (int y = 0; y < Chunk::SIZE; y++) {
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
		if (rerender) {
			rerender = false;
			reshape();
			recalculateLights();
		}
		Shaders::DEFAULT.bind();
		ChunkRenderer::renderChunk(this);
	}

	void Chunk::reshape() {
		for (int x = 0; x < Chunk::SIZE; x++) {
			for (int y = 0; y < Chunk::SIZE; y++) {
				if (tiles[x][y] != &Tiles::AIR) {
					if (tiles[x][y] == nullptr) tiles[x][y] = &Tiles::AIR;
					glm::vec2 state = tiles[x][y]->getShape(this, x, y);

					states[x][y] = state;
				}
			}
		}
	}
	void Chunk::recalculateNextLights() {
		int step = 3;
		double density = 0.1;
		for ( int x = 0; x < Chunk::SIZE; x++) {
			for ( int y = 0; y < Chunk::SIZE; y++) {

	
				if (tiles[x][y] == &Tiles::AIR) {
					renderLights[x][y] = Constants::WHITE_LIGHT;
					continue;
				}
				glm::vec3 light = lights[x][y];
				double R = light.x + 0.0;
				double G = light.y + 0.0;
				double B = light.z + 0.0;


				for (int xx = -step; xx < step + 1; xx++) {
					for (int yy = -step; yy < step + 1; yy++) {
						glm::vec3 l2 = getLight(x + xx, y + yy);
	
						double dist = MathFunc::distance(glm::vec2(x, y), glm::vec2(x + xx + 0.5, y + yy + 0.5));
						dist /= 2.5;
						dist = MathFunc::clamp(dist, 0, 1);

						if (l2[0] > R || l2[1] > G || l2[2] > B) {
							R = MathFunc::lerp(R, l2[0], density);
							G = MathFunc::lerp(G, l2[1], density);
							B = MathFunc::lerp(B, l2[2], density);
						}


					}
				}
				renderLights[x][y] = glm::vec3(R, G, B);
			}
		}
	}
	void Chunk::recalculateLights() {
		int step = 2;
		glm::vec2 pos;
		for (int x = getX() - step; x < getX() + step + 1; x++) {
			for (int y = getY() - step; y < getY() + step + 1; y++) {
				if (x != getX() && y != getY()) {
					pos.x = x;
					pos.y = y;
					if (world->doesChunkExist(pos)) {
						Chunk* chunk = world->getChunk(pos);
						chunk->recalculateNextLights();

					}
				}
				else {
					recalculateNextLights();
				}
			}
		}
	}
	glm::vec3 Chunk::getRenderLight(int x, int y) {
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
				return c2->getRenderLight(x, y);
			}
		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return Constants::NO_LIGHT;
		}
		return renderLights[x][y];
	}
	glm::vec3 Chunk::getLight(int x, int y) {
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
				return c2->getLight(x, y);
			}
		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return Constants::WHITE_LIGHT;
		}
		return lights[x][y];
	}
	void Chunk::setLight(int x, int y, glm::vec3 light) {
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
				c2->setLight(x, y, light);
				return;
			}

		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return;
		}

		lights[x][y] = light;
		markForRerender();
	}
	float Chunk::getDistortion(int x, int y) {
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
				return c2->getDistortion(x, y);
			}
		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return 0;
		}
		return distortion[x][y];
	}
	void Chunk::setDistortion(int x, int y, float distorted) {
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
				c2->setDistortion(x, y, distorted);
				return;
			}

		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return;
		}

		distortion[x][y] = distorted;
	}
	glm::vec2 Chunk::getState(int x, int y) {
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
				return c2->getState(x, y);
			}
		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return glm::vec2(0, 0);
		}
		return states[x][y];
	}
	void Chunk::setState(int x, int y, glm::vec2 state) {
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
				c2->setState(x, y, state);
				return;
			}

		}

		if (x < 0 || y < 0 || x > Chunk::SIZE - 1 || y > Chunk::SIZE - 1) {
			return;
		}

		states[x][y] = state;
		markForRerender();
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
	void Chunk::setTile(int x, int y, Tile* tile) {
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
		tiles[x][y] = tile;
		distortion[x][y] = tile->getDistortionFactor();
		lights[x][y] = tile->getLightValue();
		markForRerender();
	}
}