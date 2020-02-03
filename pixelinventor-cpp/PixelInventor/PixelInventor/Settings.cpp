#include "Settings.h"

using namespace PixelInventor;
namespace PixelInventor {
	int Settings::frameSkip = 1;
	int Settings::ATTACK = GLFW_MOUSE_BUTTON_1;
	int Settings::USE = GLFW_MOUSE_BUTTON_3;
	int Settings::UP = GLFW_KEY_W;
	int Settings::DOWN = GLFW_KEY_S;
	int Settings::LEFT = GLFW_KEY_A;
	int Settings::RIGHT = GLFW_KEY_D;
	int Settings::ZOOM_IN = GLFW_KEY_EQUAL;
	int Settings::ZOOM_OUT = GLFW_KEY_MINUS;

	bool Settings::clouds = false;
	bool Settings::distortion = false;
	bool Settings::smoothLights = false;

	bool Settings::keys[1000];
	bool Settings::pressed[1000];
	bool Settings::buttons[10];
	bool Settings::mouseDown[10];

	bool Settings::isMouseButtonDown(unsigned int button) {
		return Settings::buttons[button];
	}

	bool Settings::isKeyDown(unsigned int key) {
		return Settings::keys[key];
	}

	bool Settings::isMouseButtonPressed(unsigned int button) {
		if (!isMouseButtonDown(button)) mouseDown[button] = false;
		if (isMouseButtonDown(button) && !mouseDown[button]) {
			buttons[button] = true;
			return true;
		}
		return false;
	}

	bool Settings::isKeyPressed(unsigned int key) {
		if (!isKeyDown(key)) pressed[key] = false;
		if (isKeyDown(key) && !pressed[key]) {
			keys[key] = true;
			return true;
		}
		return false;
	}
}
