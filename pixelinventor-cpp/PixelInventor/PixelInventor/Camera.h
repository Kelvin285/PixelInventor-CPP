#pragma once
#include "Chunk.h"
namespace PixelInventor {
	class Camera {
	public:
		static float X, Y;
		const static int VIEW_X = (int)(16.0 * (4.0 / Chunk::SIZE));
		const static int VIEW_Y = (int)(8.0 * (4.0 / Chunk::SIZE));
		static float zoom;
	};
}