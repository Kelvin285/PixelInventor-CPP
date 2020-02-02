#include "Chunk.h"
#include "ChunkRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Textures.h"
#include "Shaders.h"
#include <chrono>
#include <ctime>
#include "Constants.h"

namespace PixelInventor {
	Chunk::Chunk() {

	}
	Chunk::~Chunk() {
		glDeleteVertexArrays(1, &vaoHandle);
		glDeleteBuffers(1, &buffer);
	}

	void Chunk::markForRerender() {
		this->rerender = true;
	}

	unsigned int Chunk::getBuffer() {
		return buffer;
	}

	unsigned int Chunk::getVao() {
		return vaoHandle;
	}

	void Chunk::update() {

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
}