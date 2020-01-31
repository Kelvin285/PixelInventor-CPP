#pragma once
#include "World.h"
#include "Settings.h"
namespace PixelInventor {
	class PixelInventor {

	public:
		PixelInventor();
		~PixelInventor();
		static PixelInventor* GAME;
		World world;
	private:
		void start();
		void update();
		void render();
	};
}


