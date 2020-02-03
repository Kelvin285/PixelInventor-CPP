#pragma once
namespace PixelInventor
{
	class World;
	class Chunk;
	class ChunkGenerator {
	public:
		ChunkGenerator(World* world);
		~ChunkGenerator();

		void generateChunk(Chunk* chunk);
	private:
		World* world;
	};
}