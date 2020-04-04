#include "Events.h"

float Events::w;
float Events::left;
float Events::height;

void Events::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//TODO: Add key presses to settings
}

void Events::mousePos(GLFWwindow* window, double x, double y)
{
	Mouse::x = (float)x;
	Mouse::y = (float)y;
}

void Events::mouseClick(GLFWwindow* window, int button, int press, int undefined)
{
	//if (GuiRenderer::currentScreen == 0)
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Mouse::locked = true;

	//TODO: add mouse clicks to settings
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
