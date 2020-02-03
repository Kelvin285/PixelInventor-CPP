#include "Tile.h"
#include "Textures.h"
namespace PixelInventor {
	
	MultiTile::MultiTile(std::string location, unsigned int texture, int sizeX, int sizeY) {
		this->location = location;
		this->texture = texture;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->multi = true;
		this->overlay = Textures::TILE_AIR;
		this->tileTemplate = Textures::TEMPLATE_SQUARED;
		this->visible = true;
	}

	int MultiTile::getSizeX() {
		
		return this->sizeX;
	}

	int MultiTile::getSizeY() {
		return this->sizeY;
	}

	glm::vec2 MultiTile::getTile(int x, int y) {
		if (this->sizeX == 0) this->sizeX = 4;
		if (this->sizeY == 0) this->sizeY = 4;
		return glm::vec2(x % sizeX, y % sizeY);
	}
}