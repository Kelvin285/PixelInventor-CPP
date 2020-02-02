#pragma once

namespace PixelInventor {
	
	class Chunk {
	public:
		Chunk();
		~Chunk();
		void markForRerender();
		void update();
		void render();
		unsigned int getBuffer();
		unsigned int getVao();
		static const unsigned int SIZE = 4;
	private:
		bool rerender = true;
		unsigned int buffer = 0;
		unsigned int vaoHandle;
		bool genBuffers = true;
	};
}