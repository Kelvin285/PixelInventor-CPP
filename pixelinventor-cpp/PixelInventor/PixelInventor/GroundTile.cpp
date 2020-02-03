#include "Tile.h"
#include "Chunk.h"
#include "Tiles.h"
#include "Textures.h"
#include <iostream>
namespace PixelInventor {
	GroundTile::GroundTile(std::string location, unsigned int texture, int sizeX, int sizeY) {
		this->location = location;
		this->texture = texture;
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->multi = true;
		this->overlay = Textures::TILE_AIR;
		this->tileTemplate = Textures::TEMPLATE_SQUARED;
		this->visible = true;
		this->ground = true;
	}
	
	glm::vec2 GroundTile::getShape(Chunk* chunk, int x, int y) {
		int state = 0;
		if (chunk->getTile(x, y + 1) != &Tiles::AIR) {
			state += 1;
		}
		if (chunk->getTile(x, y - 1) != &Tiles::AIR) {
			state += 4;
		}
		if (chunk->getTile(x - 1, y) != &Tiles::AIR) {
			state += 2;
		}
		if (chunk->getTile(x + 1, y) != &Tiles::AIR) {
			state += 8;
		}

		if (state == 7 && chunk->getTile(x + 1, y - 1) == &Tiles::AIR) {
			state = 2;
		}

		if (state == 7 && chunk->getTile(x + 1, y + 1) == &Tiles::AIR) {
			state = 2;
		}

		if (state == 13 && chunk->getTile(x - 1, y - 1) == &Tiles::AIR) {
			state = 8;
		}

		if (state == 13 && chunk->getTile(x - 1, y + 1) == &Tiles::AIR) {
			state = 8;
		}

		if (state == 11 && chunk->getTile(x - 1, y - 1) == &Tiles::AIR) {
			state = 1;
		}

		if (state == 11 && chunk->getTile(x + 1, y - 1) == &Tiles::AIR) {
			state = 1;
		}

		if (state == 14 && chunk->getTile(x - 1, y + 1) == &Tiles::AIR) {
			state = 4;
		}

		if (state == 14 && chunk->getTile(x + 1, y + 1) == &Tiles::AIR) {
			state = 4;
		}

		if (state == 2 && chunk->getTile(x, y - 1) == &Tiles::AIR) {
			state = 16;
		}

		if (state == 4 && chunk->getTile(x - 1, y) == &Tiles::AIR) {
			state = 17;
		}

		if (state == 8 && chunk->getTile(x, y - 1) == &Tiles::AIR) {
			state = 18;
		}

		if (state == 1 && chunk->getTile(x - 1, y) == &Tiles::AIR) {
			state = 19;
		}

		return glm::vec2(state, 0);
	}
}