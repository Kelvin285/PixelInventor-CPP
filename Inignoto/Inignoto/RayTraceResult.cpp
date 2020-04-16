#include "RayTraceResult.h"

const RayTraceResult::Direction RayTraceResult::UP = { 0, 1, 0 };
const RayTraceResult::Direction RayTraceResult::DOWN = { 0, -1, 0 };
const RayTraceResult::Direction RayTraceResult::LEFT = { -1, 0, 0 };
const RayTraceResult::Direction RayTraceResult::RIGHT = { 1, 0, 0 };
const RayTraceResult::Direction RayTraceResult::FRONT = { 0, 0, -1 };
const RayTraceResult::Direction RayTraceResult::BACK = { 0, 0, 1 };

RayTraceResult::RayTraceResult(RayTraceType type, TilePos position, glm::vec3 hit)
{
	this->type = type;
	this->position = position;
	this->hit = hit;

	glm::vec3 p(position.x, position.y, position.z);
	glm::vec3 n((p - hit) * glm::vec3(-1.0));

	Direction direction = getDirection(n.x, n.y, n.z);
	this->direction = direction;
}

RayTraceResult::Direction RayTraceResult::getDirection(double X, double Y, double Z)
{
	int x = (int)floor(X);
	int y = (int)floor(Y);
	int z = (int)floor(Z);

	if (Y < 1.0 && Y > 0.0) y = 0;
	if (Z < 1.0 && Z > 0.0) z = 0;
	if (X < 1.0 && X > 0.0) x = 0;

	if (x == -1 && y == 0 && z == 0) {
		return LEFT;
	}
	if (x == 1 && y == 0 && z == 0) {
		return RIGHT;
	}
	if (x == 0 && y == 1 && z == 0) {
		return UP;
	}
	if (x == 0 && y == -1 && z == 0) {
		return DOWN;
	}
	if (x == 0 && y == 0 && z == 1) {
		return BACK;
	}
	if (x == 0 && y == 0 && z == -1) {
		return FRONT;
	}

	return { 0, 0, 0 };
}
