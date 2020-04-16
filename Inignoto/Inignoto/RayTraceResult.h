#pragma once
#include "glm/glm.hpp"
#include "TilePos.h"
class RayTraceResult
{
public:
	enum RayTraceType {
		TILE, ENTITY, EMPTY
	};
	struct Direction {
		int x, y, z;
	};
	const static Direction UP, DOWN, LEFT, RIGHT, FRONT, BACK;

	RayTraceResult(RayTraceType type, TilePos position, glm::vec3 hit);

	RayTraceType getType() {
		return this->type;
	}

	TilePos getPosition() {
		return this->position;
	}

	glm::vec3 getHit() {
		return this->hit;
	}

private:
	RayTraceType type;
	TilePos position;
	glm::vec3 hit;
	Direction direction;

	Direction getDirection(double X, double Y, double Z);

};

