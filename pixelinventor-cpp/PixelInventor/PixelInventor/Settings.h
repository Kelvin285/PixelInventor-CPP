#pragma once
#include <GLFW/glfw3.h>

namespace PixelInventor {
	class Settings {
	public:
		static int frameSkip;
		static bool distortion;
		static bool smoothLights;
		static bool clouds;
		static int UP, DOWN, LEFT, RIGHT, ZOOM_IN, ZOOM_OUT, ATTACK, USE;
		static bool keys[1000];
		static bool pressed[1000];
		static bool buttons[10];
		static bool mouseDown[10];

		static bool isMouseButtonDown(unsigned int button);
		static bool isMouseButtonPressed(unsigned int button);

		static bool isKeyDown(unsigned int key);
		static bool isKeyPressed(unsigned int key);
	private:
		
	};
}