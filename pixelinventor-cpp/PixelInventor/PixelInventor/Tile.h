#pragma once
#include <string>
#include <glm/glm.hpp>
namespace PixelInventor {
	class Chunk;
	class Tile {

	public:
		std::string location;
		unsigned int texture;
		unsigned int overlay;
		glm::vec3 light_value = glm::vec3(0, 0, 0);
		unsigned int tileTemplate;
		bool visible;
		bool multi;
		bool ground;
		Tile() {}
		Tile(std::string location, unsigned int texture);
		~Tile();

		std::string getLocation() {
			return location;
		}

		unsigned int getOverlay() {
			return overlay;
		}

		unsigned int getTilingTemplate() {
			return tileTemplate;
		}

		unsigned int getTexture() {
			return texture;
		}

		void update(glm::vec2 pos, Chunk* chunk) {

		}

		float getUpdatePercent() {
			return 0.0;
		}

		float getDistortionFactor() {
			return 0.0;
		}

		float getNaturalDistortion() {
			return 0.0;
		}

		glm::vec3 getLightValue() {
			return light_value;
		}

		void setLightValue(glm::vec3 light_value) {
			this->light_value = light_value;
		}

		bool isVisible() {
			return this->visible;
		}

		void setVisible(bool visible) {
			this->visible = visible;
		}

		void setOverlay(unsigned int tile) {
			this->overlay = tile;
		}

		void setTilingTemplate(unsigned int temp) {
			this->tileTemplate = temp;
		}

		virtual glm::vec2 getShape(Chunk* chunk, int x, int y);

		void setMulti(bool multi) {
			this->multi = multi;
		}

		bool isMulti() {
			return this->multi;
		}
		
			
	};

	class MultiTile : public Tile {
	public:
		MultiTile() {}
		MultiTile(std::string location, unsigned int texture, int sizeX, int sizeY);

		int getSizeX();

		int getSizeY();

		glm::vec2 getTile(int x, int y);
		
		int sizeX, sizeY;
		
	};

	class GroundTile : public MultiTile {
	public:
		GroundTile() {}
		GroundTile(std::string location, unsigned int texture, int sizeX, int sizeY);

		 float getNaturalDistortion() {
			return 0.2f;
		}

		 glm::vec2 getShape(Chunk* chunk, int x, int y);
	
	};
}