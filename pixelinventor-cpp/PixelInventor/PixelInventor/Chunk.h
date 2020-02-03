#pragma once
#include <glm/glm.hpp>
#include <random>
namespace PixelInventor {
	class Tile;
	class World;
	class Chunk {
	public:
		Chunk(int x, int y, World* world);
		~Chunk();
		void markForRerender();
		void update();
		void render();

		int getX() {
			return X;
		}

		int getY() {
			return Y;
		}

		void reshape();
		void recalulateNextLights();
		void recalculateLights();
		glm::vec3 getRenderLight(int x, int y);
		glm::vec3 getLight(int x, int y);
		void setLight(int x, int y, glm::vec3 light);
		float getDistortion(int x, int y);
		void setDistortion(int x, int y, float distorted);
		glm::vec2 getState(int x, int y);
		void setState(int x, int y, glm::vec2 state);
		Tile* getTile(int x, int y);
		void setTile(int x, int y, Tile tile);

		static const unsigned int SIZE = 4;

		int X;
		int Y;
		Tile* tiles[Chunk::SIZE][Chunk::SIZE];
		glm::vec2 states[Chunk::SIZE][Chunk::SIZE];
		float distortion[Chunk::SIZE][Chunk::SIZE];
		glm::vec3 lights[Chunk::SIZE][Chunk::SIZE];
		glm::vec3 renderLights[Chunk::SIZE][Chunk::SIZE];

		World* world;

	private:
		bool rerender = true;
		
	};
}