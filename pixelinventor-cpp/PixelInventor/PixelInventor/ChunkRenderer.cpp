#include "ChunkRenderer.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Constants.h"
#include "Textures.h"
#include <glm/glm.hpp>
#include "Tile.h"
#include "Camera.h"
namespace PixelInventor {
	
	void ChunkRenderer::renderChunk(Chunk* chunk) {
		double w = 21.0;
		for (int x = 0; x < Chunk::SIZE; x++) {
			for (int y = 0; y < Chunk::SIZE; y++) {
				renderTile(chunk, x, y);
			}
		}
	}
	void ChunkRenderer::renderTile(Chunk* chunk, int x, int y) {
		Tile* tile = chunk->tiles[x][y];
		if (tile->isVisible() == false) return;
		double X = x * Constants::tilesize + chunk->getX() * Constants::tilesize * Chunk::SIZE - Camera::X;
		double Y = y * Constants::tilesize + chunk->getY() * Constants::tilesize * Chunk::SIZE - Camera::Y;
		glm::vec2 state = chunk->states[x][y];
		glm::vec2 mstate = chunk->states[x][y];
		double w = 1.0 / 20.0;
		double h = 0.99;

		double w2 = 1.0 / 20.0;
		double h2 = 0.99;
		if (tile->isMulti()) {
			MultiTile* multi = (MultiTile*)tile;
			mstate = multi->getTile(x, y);
			w2 = 1.0 / multi->getSizeX();
			h2 = 0.99 / multi->getSizeY();
		}
		unsigned int overlay = Textures::TILE_AIR;
		if (tile->getOverlay() != 0) {
			overlay = tile->getOverlay();
		}
		
		Constants::spriteRenderer->DrawSprite(tile->getTexture(), tile->getTilingTemplate(), tile->getOverlay(), glm::vec2(X, Y), glm::vec2(Constants::tilesize, Constants::tilesize), 0.0f, chunk->renderLights[x][y], glm::vec4(mstate.x * w2, mstate.y * h2, w2, h2), glm::vec4(state.x * w, state.y * h, w, h), glm::vec4(state.x * w, state.y * h, w, h));

	}
}