#include "Input.h"
#include "Inignoto.h"
#include <iostream>
#include <set>

void Input::doInput() {
	/*
	GuiRenderer* renderer = Inignoto::game->guiRenderer;
	if (renderer->getOpenScreen() == null) {
		doGameInput();
	}
	*/
	doGameInput();

	Mouse::update();

}

void Input::updateCamera() {
	float speed = 0.01f;
	float rotSpeed = 2.0f;
	if (Settings::RIGHT.isPressed()) {
		float yaw = 90;
		Camera::position.x += speed * Camera::getForward(0, Camera::rotation.y + yaw).x *FPSCounter::getDelta();
		Camera::position.y += speed * Camera::getForward(0, Camera::rotation.y + yaw).y * FPSCounter::getDelta();
		Camera::position.z += speed * Camera::getForward(0, Camera::rotation.y + yaw).z * FPSCounter::getDelta();
	}

	if (Settings::LEFT.isPressed()) {
		float yaw = -90;
		Camera::position.x += speed * Camera::getForward(0, Camera::rotation.y + yaw).x * FPSCounter::getDelta();
		Camera::position.y += speed * Camera::getForward(0, Camera::rotation.y + yaw).y * FPSCounter::getDelta();
		Camera::position.z += speed * Camera::getForward(0, Camera::rotation.y + yaw).z * FPSCounter::getDelta();
	}

	if (Settings::FORWARD.isPressed()) {
		float yaw = 180;
		float pitch = 0;
		Camera::position.x += speed * Camera::getForward(0, Camera::rotation.y + yaw).x * FPSCounter::getDelta();
		Camera::position.z += speed * Camera::getForward(0, Camera::rotation.y + yaw).z * FPSCounter::getDelta();
	}

	if (Settings::BACKWARD.isPressed()) {
		float yaw = 0;
		float pitch = 0;
		Camera::position.x += speed * Camera::getForward(0, Camera::rotation.y + yaw).x * FPSCounter::getDelta();
		Camera::position.z += speed * Camera::getForward(0, Camera::rotation.y + yaw).z * FPSCounter::getDelta();
	}

	if (Settings::JUMP.isPressed()) {
		Camera::position.y += speed * FPSCounter::getDelta();
	}

	if (Settings::SNEAK.isPressed()) {
		Camera::position.y -= speed * FPSCounter::getDelta();
	}
}

void Input::doGameInput() {
	updateCamera();
	
	if (Mouse::locked) {
		Camera::rotation.y -= (Mouse::x - Mouse::lastX) * Settings::MOUSE_SENSITIVITY * FPSCounter::getDelta();
		Camera::rotation.x -= (Mouse::y - Mouse::lastY) * Settings::MOUSE_SENSITIVITY * FPSCounter::getDelta();

		if (Camera::rotation.x < -90) Camera::rotation.x = -90;
		if (Camera::rotation.x > 90) Camera::rotation.x = 90;
	}
}