#pragma once
#include "VBO.h"
#include <vector>
#include <glm/glm.hpp>
#include "BlockBuilder.hpp"
class Chunk;
class ChunkBuilder {
public:
	static int buildChunk(Chunk& chunk);
	static uint32_t buildChunk(Chunk& chunk, std::vector<glm::vec3>* vertices, std::vector<uint32_t>* indices, std::vector<glm::vec2>* texCoords, int index);
};