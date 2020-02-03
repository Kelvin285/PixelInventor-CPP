#pragma once
#include <math.h>
#include <glm/glm.hpp>
#include "Chunk.h"
#include "Constants.h"
#include "Camera.h"
namespace PixelInventor {
	class MathFunc {
	public:
		static const float RAD;
		static const float DEG;

		static float distance(glm::vec2 a, glm::vec2 b) {
			return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
		}

		static float lerp(float a, float b, float c) {
			return a + c * (b - a);
		}

		static int getChunkPosFor(float x) {
			return (int)floor(x / (Chunk::SIZE * Constants::tilesize));
		}

		static int getTilePosFor(float x) {
			return (int)floor(x / Constants::tilesize);
		}

		static float abs(float x) {
			return x < 0 ? -x : x;
		}

		static float clamp(float x, float min, float max) {
			return x < min ? min : x > max ? max : x;
		}

		static int clamp(int x, int min, int max) {
			return x < min ? min : x > max ? max : x;
		}

		static int toStaticZoomedCoordsY(int x) {
			double mx = x - Constants::SCREEN_HEIGHT / 2;
			mx /= (Camera::zoom + 1);
			mx += Constants::SCREEN_HEIGHT / 2;
			return (int)mx;
		}
		static int toStaticZoomedCoordsX(int x) {
			double mx = x - Constants::SCREEN_WIDTH / 2;
			mx /= (Camera::zoom + 1);
			mx += Constants::SCREEN_WIDTH / 2;
			return (int)mx;
		}

		static int toZoomedCoordsY(int x) {
			int width, height;
			glfwGetWindowSize(Constants::window, &width, &height);
			double mx = x - height / 2;
			mx /= (Camera::zoom + 1);
			mx += height / 2;
			return (int)mx;
		}

		static int toZoomedCoordsX(int x) {
			int width, height;
			glfwGetWindowSize(Constants::window, &width, &height);
			double mx = x - width / 2;
			mx /= (Camera::zoom + 1);
			mx += width / 2;
			return (int)mx;
		}
	};
}