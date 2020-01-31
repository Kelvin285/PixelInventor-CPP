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
	private:
		bool rerender = true;
		unsigned int buffer = 0;
		bool genBuffers = true;
	};
}