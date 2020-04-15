#pragma once
#include "glm/glm.hpp"
class Camera
{
public:
	static glm::vec3 position;
	static glm::vec3 rotation;

	static const float BASE_REACH;
	static float REACH_DISTANCE;

	static void update();

	static glm::vec3 getUp();
	static glm::vec3 getDown();
	static glm::vec3 getForward();
	static glm::vec3 getRight();
	static glm::vec3 getForward(float PITCH, float YAW);
};

