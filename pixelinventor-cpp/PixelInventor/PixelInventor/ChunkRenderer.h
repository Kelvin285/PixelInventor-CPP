#pragma once
#include "Chunk.h"
namespace PixelInventor {
	class ChunkRenderer {
	public:
		static void renderChunk(Chunk* chunk);
		static void renderTile(Chunk* chunk, int x, int y);
	};
}