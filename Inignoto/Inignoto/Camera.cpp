#include "Camera.h"
#include <math.h>
#include "Inignoto.h"

glm::vec3 Camera::position = glm::vec3(2, 2, 2);
glm::vec3 Camera::rotation;

void Camera::update() {
	if (rotation.x < -89) rotation.x = -89;
	if (rotation.x > 89) rotation.x = 89;

	Inignoto* game = Inignoto::game;
}

glm::vec3 Camera::getUp() {
	return getForward(-(rotation.x + 90), rotation.y);
}

glm::vec3 Camera::getDown() {
	return getForward(-(rotation.x - 90), rotation.y);
}

glm::vec3 Camera::getForward() {
	return getForward(-rotation.x, rotation.y);
}

glm::vec3 Camera::getRight() {
	return getForward(0, rotation.y + 90);
}

glm::vec3 Camera::getForward(float PITCH, float YAW) {
	float pitch = PITCH;
	float yaw = YAW - 90;
	float radians = 3.14f / 180.0f;
	return glm::vec3((float)cos(radians * yaw) * (float)cos(radians * pitch), (float)sin(radians * pitch), (float)sin(radians * yaw) * (float)cos(radians * pitch));
}