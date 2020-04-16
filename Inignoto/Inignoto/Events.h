#pragma once
#include <GLFW/glfw3.h>
#include "Mouse.h"
#include "Utils.h"
#include "GuiRenderer.h"

class Events
{
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePos(GLFWwindow* window, double x, double y);
	static void mouseClick(GLFWwindow* window, int button, int press, int undefined);
	static void windowFocus(GLFWwindow* window, int focused);
	static void windowSize(GLFWwindow* window, int width, int height);
	static float w;
	static float left;
	static float height;
};

