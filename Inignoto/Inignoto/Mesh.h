#pragma once
#include "VBO.h"
#include <glm/glm.hpp>
#include <vector>

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
};