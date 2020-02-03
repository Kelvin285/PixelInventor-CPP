#pragma once
#include "World.h"

namespace PixelInventor {
	class PixelInventor {

	public:
		PixelInventor();
		~PixelInventor();
		World world;
		
	private:
		void start();
		void update();
		void render();
		void initGL();
	};
}


