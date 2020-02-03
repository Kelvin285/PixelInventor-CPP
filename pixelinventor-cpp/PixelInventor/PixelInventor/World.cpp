#include "World.h"
#include <iterator>
#include "HashMap.h"
#include <string>
#include <math.h>
#include "Constants.h"
#include "MathFunc.h"
namespace PixelInventor {
	HashMap<std::string, Chunk*> loadedChunks;

	World::World() {

	}

	World::~World() {
		for (unsigned int i = 0; i < loadedChunks.size(); i++) {
			delete loadedChunks.get(loadedChunks.getKeyAt(i));
		}
		loadedChunks.clear();
	}

	int I = 0;
	void World::update() {
		
		for (unsigned int i = 0; i < loadedChunks.size(); i++) {
			loadedChunks.get(loadedChunks.getKeyAt(i))->update();
		}
		I++;
		if (I > 2) {
			I = 0;
			const int X = (int)(Camera::X / (Chunk::SIZE * Constants::tilesize)) + 7;
			const int Y = (int)(Camera::Y / (Chunk::SIZE * Constants::tilesize)) + 4;

			glm::vec2 pt;

			for (int x = X + -Camera::VIEW_X * 2; x < X + Camera::VIEW_X * 2 + 1; x++) {
				for (int y = Y + -Camera::VIEW_Y * 2; y < Y + Camera::VIEW_Y * 2 + 1; y++) {
					pt.x = x;
					pt.y = y;

					if (MathFunc::abs(x - X) <= Camera::VIEW_X && MathFunc::abs(y - Y) <= Camera::VIEW_Y) {
						if (!loadedChunks.containsKey(std::to_string(x) + "," + std::to_string(y))) {
							addChunk(pt);
							reshapeChunk(pt);
						}
					}
					else {
						if (loadedChunks.containsKey(std::to_string(x) + "," + std::to_string(y))) {
							loadedChunks.remove(std::to_string(x) + "," + std::to_string(y));
						}
					}
					
				}
			}
			


		}
	}

	void World::addChunk(glm::vec2 pos) {
		Chunk* chunk = new Chunk((int)pos.x, (int)pos.y, this);
		//generator.generate(chunk);
		int x = (int)pos.x;
		int y = (int)pos.y;
		loadedChunks.put(std::to_string(x) + "," + std::to_string(y), chunk);
	}

	void World::render() {
		for (unsigned int i = 0; i < loadedChunks.size(); i++) {
			std::string str = loadedChunks.getKeyAt(i);
			loadedChunks.get(str)->render();
		}
	}
	
	void World::reshapeChunk(glm::vec2 pos) {
		for (int xx = -1; xx < 2; xx++) {
			for (int yy = -1; yy < 2; yy++) {
				reshapeNextChunk(glm::vec2(pos.x + xx, pos.y + yy));
			}
		}
	}

	void World::reshapeNextChunk(glm::vec2 pos) {
		if (doesChunkExist(pos)) {
			Chunk* chunk = getChunk(pos);
			chunk->reshape();
			chunk->markForRerender();
		}
	}

	Chunk* World::getChunk(glm::vec2 pos) {
		int x = (int)pos.x;
		int y = (int)pos.y;
		return loadedChunks.get(std::to_string(x) + "," + std::to_string(y));
	}

	bool World::doesChunkExist(glm::vec2 pos) {
		int x = (int)pos.x;
		int y = (int)pos.y;
		return loadedChunks.containsKey(std::to_string(x) + "," + std::to_string(y));
	}
}