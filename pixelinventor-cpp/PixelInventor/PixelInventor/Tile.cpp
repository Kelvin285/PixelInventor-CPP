#include "Tile.h"
#include "Chunk.h"
#include "Textures.h"
namespace PixelInventor {
	Tile::Tile(std::string location, unsigned int texture) {
		this->texture = texture;
		this->location = location;
		this->overlay = Textures::TILE_AIR;
		this->tileTemplate = Textures::TEMPLATE_SQUARED;
		this->visible = true;
	}
	Tile::~Tile() {

	}

	glm::vec2 Tile::getShape(Chunk* chunk, int x, int y) {
		return chunk->states[x][y];
	}
}