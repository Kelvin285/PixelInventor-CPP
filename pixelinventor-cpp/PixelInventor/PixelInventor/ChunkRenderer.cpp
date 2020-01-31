#include "ChunkRenderer.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace PixelInventor {
	float positions[6] = {
	   -0.5f, -0.5f,
		0.0f,  0.5f,
		0.5f, -0.5f
	};
	void ChunkRenderer::renderChunk(Chunk* chunk) {
		glBindBuffer(GL_ARRAY_BUFFER, chunk->getBuffer());
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}