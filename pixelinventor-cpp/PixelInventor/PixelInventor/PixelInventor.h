#pragma once
#include "World.h"

namespace PixelInventor {
	class PixelInventor {

	public:
		PixelInventor();
		~PixelInventor();
		World world;
		const static int SCREEN_WIDTH = (unsigned int)((1920 / 2) / 16) * 16;
		const static int SCREEN_HEIGHT = (unsigned int)((1080 / 2) / 16) * 16;
	private:
		void start();
		void update();
		void render();
		void initGL();
	};
}


