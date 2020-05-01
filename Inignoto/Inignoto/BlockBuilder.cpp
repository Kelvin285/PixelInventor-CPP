#include "BlockBuilder.hpp"
#include "Inignoto.h"

int BlockBuilder::buildMesh(Tile* tile, float x, float y, float z) {

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<uint32_t> indices;

	int index = 0;
	TileData data(tile->getID());
	if (tile->isFull() && tile->isVisible()) {
		index = addFace(x, y, z, BlockFace::LEFT, data, &vertices, &texCoords, &indices, index);
		index = addFace(x, y, z, BlockFace::RIGHT, data, &vertices, &texCoords, &indices, index);
		index = addFace(x, y, z, BlockFace::BACK, data, &vertices, &texCoords, &indices, index);
		index = addFace(x, y, z, BlockFace::FRONT, data, &vertices, &texCoords, &indices, index);
		index = addFace(x, y, z, BlockFace::DOWN, data, &vertices, &texCoords, &indices, index);
		index = addFace(x, y, z, BlockFace::UP, data, &vertices, &texCoords, &indices, index);
	}

	std::vector<Vertex> verts;
	verts.resize(vertices.size());
	for (size_t i = 0; i < vertices.size(); i++) {
		glm::bvec3 nanverts = glm::isnan(vertices[i]);
		glm::bvec2 nantex = glm::isnan(texCoords[i]);
		Vertex v = {
			{!nanverts[0] ? vertices[i][0] : 0, nanverts[1] ? !vertices[i][1] : 0, !nanverts[2] ? vertices[i][2] : 0},
			{1, 1, 1},
			{!nantex[0] ? texCoords[i][0] : 0, !nantex[1] ? texCoords[i][1] : 0}
		};

		verts[i] = v;
	}
	CreateVBO create;
	create.vertices = verts;
	create.indices = indices;
	return Inignoto::game->addVBO(create);
}