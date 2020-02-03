#pragma once
#include "SpriteRenderer.h"
#include <glm/glm.hpp>

namespace PixelInventor {
	class Constants {
	public:
		static SpriteRenderer* spriteRenderer;
		static const unsigned int tilesize = 16;
		static glm::vec3 NO_LIGHT;
		static glm::vec3 WHITE_LIGHT;
		static GLFWwindow* window;
	};
}