#pragma once

namespace PixelInventor {
	class PixelInventor {

	public:
		PixelInventor();
		~PixelInventor();
		static PixelInventor* GAME;
	private:
		void start();
		void update();
		void render();
	};
}


