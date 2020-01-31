#include "Chunk.h"
#include "ChunkRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace PixelInventor {
	Chunk::Chunk() {

	}
	Chunk::~Chunk() {

	}

	void Chunk::markForRerender() {
		this->rerender = true;
	}

	unsigned int Chunk::getBuffer() {
		return buffer;
	}

	void Chunk::update() {

	}

	void Chunk::render() {
		if (genBuffers) {
			glGenBuffers(1, &buffer);
			genBuffers = false;
		}
		if (rerender) {
			
		}
		ChunkRenderer::renderChunk(this);
	}
}