#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>
#include <vector>
#include "Tile.h"
#include "Tiles.h"
#include "VBO.h"
#include "Tiledata.h"
#include "Textures.h"

class BlockBuilder {
public:


	static int buildMesh(Tile* tile, float x, float y, float z);
	static int addFace(float x, float y, float z, BlockFace face, TileData& data, std::vector<glm::vec3>* vertices, std::vector<glm::vec2>* texCoords, std::vector<uint32_t>* indices, uint32_t index) {
		if (data.getMiningTime() > 0) {
			index = addMiningFace((int)x, (int)y, (int)z, face, data.getMiningTime(), vertices, texCoords, indices, index);
		}
		Tile* tile = Tiles::getTile(data.getTile());
		std::array<glm::vec3, 4> vertices1;
		uint32_t indices1[] = { 0, 1, 2, 2, 3, 0 };

		int scrollX = (int)x;
		int scrollY = (int)y;

		switch (face) {
		case FRONT:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 0.0f)
			};
			break;
		case BACK:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 1.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 1.0f)
			};
			break;
		case LEFT:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 0.0f, y + 0.0f, z + 1.0f)
			};
			scrollX = (int)z;
			break;
		case RIGHT:
			vertices1 = {
			glm::vec3(x + 1.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 1.0f)
			};
			scrollY = (int)z;
			break;
		case UP:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 0.0f)
			};
			scrollY = (int)z;
			break;
		case DOWN:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 0.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 0.0f)
			};
			scrollY = (int)z;
			break;
		}

		TextureSpace* space = Textures::getSpaceFor(tile->getTextureFor(face));
		if (space == nullptr) {
			std::cout << "no texture space found for texture: " << tile->getTextureFor(face) << "!" << std::endl;
			return index;
		}
		float u = (1.0f / tile->getWidth()) * (scrollX % tile->getWidth());
		float v = (1.0f / tile->getHeight()) * (scrollY % tile->getHeight());
		float w = u + (1.0f / tile->getWidth());
		float h = v + (1.0f / tile->getHeight());
		std::array<glm::vec2, 4> texCoords1 = space->getTextureCoords(Textures::IMAGE_WIDTH, Textures::IMAGE_HEIGHT, u, v, w, h);
		for (auto at : vertices1) {
			vertices->push_back(at);
		}
		for (auto at : indices1) {
			indices->push_back(index + at);
		}
		texCoords->push_back(texCoords1[2]);
		texCoords->push_back(texCoords1[3]);
		texCoords->push_back(texCoords1[0]);
		texCoords->push_back(texCoords1[1]);
		return index + vertices1.size();
	}

	static int addMiningFace(float x, float y, float z, BlockFace face, float progress, std::vector<glm::vec3>* vertices, std::vector<glm::vec2>* texCoords, std::vector<uint32_t>* indices, uint32_t index) {
		if (progress <= 0) return index;

		std::array<glm::vec3, 4> vertices1;
		uint32_t indices1[] = { 0, 1, 2, 2, 3, 0 };

		int scrollX = (int)(5 * (progress / 100.0f));
		int scrollY = 0;

		switch (face) {
		case FRONT:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 0.0f)
			};
			break;
		case BACK:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 1.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 1.0f)
			};
			break;
		case LEFT:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 0.0f, y + 0.0f, z + 1.0f)
			};
			break;
		case RIGHT:
			vertices1 = {
			glm::vec3(x + 1.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 1.0f)
			};
			break;
		case UP:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 1.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 1.0f, z + 0.0f)
			};
			break;
		case DOWN:
			vertices1 = {
			glm::vec3(x + 0.0f, y + 0.0f, z + 0.0f),
			glm::vec3(x + 0.0f, y + 0.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 1.0f),
			glm::vec3(x + 1.0f, y + 0.0f, z + 0.0f)
			};
			break;
		}

		int width = 5;
		int height = 1;

		TextureSpace* space = Textures::getSpaceFor("Inignoto:mining");
		float u = (1.0f / (float)width) * (scrollX % width);
		float v = (1.0f / (float)height) * (scrollY % height);
		float w = u + (1.0f / (float)width);
		float h = v + (1.0f / (float)height);
		std::array<glm::vec2, 4> texCoords1 = space->getTextureCoords(Textures::IMAGE_WIDTH, Textures::IMAGE_HEIGHT, u, v, w, h);
		for (auto at : vertices1) {
			vertices->push_back(at);
		}
		for (auto at : indices1) {
			indices->push_back(at);
		}
		texCoords->push_back(texCoords1[2]);
		texCoords->push_back(texCoords1[3]);
		texCoords->push_back(texCoords1[0]);
		texCoords->push_back(texCoords1[1]);
		return index + vertices1.size();
	}
};