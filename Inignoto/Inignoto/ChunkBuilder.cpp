#include "ChunkBuilder.h"
#include "Chunk.h"
#include "Inignoto.h"

int ChunkBuilder::buildChunk(Chunk& chunk) {

	int vbo = -1;
	if (chunk.voxels <= 0) return vbo;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<uint32_t> indices;
	uint32_t index = 0;
	index = buildChunk(chunk, &vertices, &indices, &texCoords, index);
	
	std::vector<Vertex> verts;
	verts.resize(vertices.size());
	for (size_t i = 0; i < vertices.size(); i++) {
		Vertex v = {
			vertices[i],
			{1, 1, 1},
			texCoords[i]
		};
		verts[i] = v;
	}
	CreateVBO create;
	create.vertices = verts;
	create.indices = indices;
	create.orthographic = false;
	create.position = chunk.pos;

	return Inignoto::game->addVBO(create);
}

uint32_t ChunkBuilder::buildChunk(Chunk& chunk, std::vector<glm::vec3>* vertices, std::vector<uint32_t>* indices, std::vector<glm::vec2>* texCoords, int index) {
	if (chunk.voxels <= 0) return index;
	
	for (size_t x = 0; x < Chunk::SIZE; x++) {
		for (size_t y = 0; y < Chunk::SIZE_Y; y++) {
			for (size_t z = 0; z < Chunk::SIZE; z++) {
				TileData& data = chunk.getTileData(x, y, z, false);
				Tile* tile = Tiles::getTile(data.getTile());
				if (tile->isFull() && tile->isVisible()) {
					if (chunk.isLocalTileNotFull(x - 1, y, z)) index = BlockBuilder::addFace(x, y, z, BlockFace::LEFT, data, vertices, texCoords, indices, index);
					if (chunk.isLocalTileNotFull(x + 1, y, z)) index = BlockBuilder::addFace(x, y, z, BlockFace::RIGHT, data, vertices, texCoords, indices, index);
					if (chunk.isLocalTileNotFull(x, y, z - 1)) index = BlockBuilder::addFace(x, y, z, BlockFace::FRONT, data, vertices, texCoords, indices, index);
					if (chunk.isLocalTileNotFull(x, y, z + 1)) index = BlockBuilder::addFace(x, y, z, BlockFace::BACK, data, vertices, texCoords, indices, index);
					if (chunk.isLocalTileNotFull(x, y + 1, z)) index = BlockBuilder::addFace(x, y, z, BlockFace::UP, data, vertices, texCoords, indices, index);
					if (chunk.isLocalTileNotFull(x, y - 1, z)) index = BlockBuilder::addFace(x, y, z, BlockFace::DOWN, data, vertices, texCoords, indices, index);
				}
			}
		}
	}
	

	return index;
}