#include "ChunkRenderer.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Constants.h"
#include "Textures.h"
#include <glm/glm.hpp>
namespace PixelInventor {
	
	void ChunkRenderer::renderChunk(Chunk* chunk) {
		Constants::spriteRenderer->DrawSprite(Textures::TILE_DIRT, Textures::TEMPLATE_MANMADE, Textures::TILE_GRASS, glm::vec2(64, 0), glm::vec2(64, 64), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec4(0.0, 0.0, 1.0 / 21.0, 1.0), glm::vec4(0, 0, 1.0 / 21.0, 1));
	}
}