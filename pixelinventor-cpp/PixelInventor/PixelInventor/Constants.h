#pragma once
#include "SpriteRenderer.h"
#include <glm/glm.hpp>

namespace PixelInventor {
	class Constants {
	public:
		static SpriteRenderer* spriteRenderer;
		static const int tilesize = 12;
		static glm::vec3 NO_LIGHT;
		static glm::vec3 WHITE_LIGHT;
		static GLFWwindow* window;
		const static int SCREEN_WIDTH = (unsigned int)((1920 / 2) / 16) * 16;
		const static int SCREEN_HEIGHT = (unsigned int)((1080 / 2) / 16) * 16;
		const static int SPACE = 30000;
	};
}