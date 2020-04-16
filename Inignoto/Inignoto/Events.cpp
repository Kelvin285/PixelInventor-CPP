#include "Events.h"
#include "Settings.h"
#include "Inignoto.h"

float Events::w;
float Events::left;
float Events::height;

void Events::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		Settings::keys[key] = true;
		Settings::pressedKey[key] = true;
	}
	if (action == GLFW_RELEASE) {
		Settings::keys[key] = false;
		Settings::pressedKey[key] = false;

	}
}

void Events::mousePos(GLFWwindow* window, double x, double y)
{
	Mouse::x = (float)x;
	Mouse::y = (float)y;
}

void Events::mouseClick(GLFWwindow* window, int button, int press, int undefined)
{
	if (Inignoto::game->guiRenderer.getOpenScreen() != nullptr) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		Mouse::locked = true;
	}
	
	Settings::buttons[button] = press == 1;
	Settings::pressedButton[button] = press == 1;
}

void Events::windowFocus(GLFWwindow* window, int focused)
{
	Utils::WINDOW_FOCUSED = focused;
}

void Events::windowSize(GLFWwindow* window, int width, int height)
{
	float aspect = (float)width / (float)height;
	float w = height * aspect;
	float left = (width - w) / 2;
	//TODO: set window viewport
	Events::w = w;
	Events::left = left;
	Events::height = height;
	Utils::FRAME_WIDTH = width;
	Utils::FRAME_HEIGHT = height;
	//Inignoto::game->framebufferResized = true;
	Utils::framebufferResized = true;
}
