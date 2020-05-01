#include "Input.h"
#include "Inignoto.h"
#include <iostream>
#include <set>
#include "InventoryScreen.h"
#include "IngameMenuScreen.h"

void Input::doInput() {
	
	GuiRenderer* renderer = &Inignoto::game->guiRenderer;
	if (renderer->getOpenScreen() == nullptr) {
		doGameInput();
	}

	if (Settings::INVENTORY.isJustPressed()) {
		if (renderer != nullptr) {
			if (renderer->getOpenScreen() != nullptr) {
				if (!(renderer->getOpenScreen()->ID == IngameMenuScreen::ID)) {
					renderer->closeScreen();
				}
			}
			else {
				renderer->openScreen(new InventoryScreen(renderer));
			}
		}
	}
	if (Settings::EXIT.isJustPressed()) {
		if (renderer != nullptr) {
			if (renderer->getOpenScreen() != nullptr) {
				renderer->closeScreen();
			}
			else {
				renderer->openScreen(new IngameMenuScreen(renderer));
			}
		}
	}
	
	doGameInput();

	Mouse::update();

}

void Input::updateCamera() {
	float speed = 0.01f;
	float rotSpeed = 2.0f;
	if (Settings::RIGHT.isPressed()) {
		float yaw = -90;
		Camera::position.x += speed * Camera::getForward(0, Camera::rotation.y + yaw).x * FPSCounter::getDelta();
		Camera::position.y += speed * Camera::getForward(0, Camera::rotation.y + yaw).y * FPSCounter::getDelta();
		Camera::position.z += speed * Camera::getForward(0, Camera::rotation.y + yaw).z * FPSCounter::getDelta();
	}

	if (Settings::LEFT.isPressed()) {
		float yaw = 90;
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
	
	if (Mouse::locked && Inignoto::game->guiRenderer.getOpenScreen() == nullptr) {
		Camera::rotation.y += (Mouse::x - Mouse::lastX) * Settings::MOUSE_SENSITIVITY * FPSCounter::getDelta();
		Camera::rotation.x += (Mouse::y - Mouse::lastY) * Settings::MOUSE_SENSITIVITY * FPSCounter::getDelta();

		if (Camera::rotation.x < -90) Camera::rotation.x = -90;
		if (Camera::rotation.x > 90) Camera::rotation.x = 90;
	}
}