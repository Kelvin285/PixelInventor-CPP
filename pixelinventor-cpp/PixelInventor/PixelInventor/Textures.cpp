#include "Textures.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
namespace PixelInventor {
	ArrayList<unsigned int*> Textures::textures;
	unsigned int Textures::CONTAINER;
	unsigned int Textures::TEMPLATE_MANMADE;
	unsigned int Textures::TEMPLATE_NONE;
	unsigned int Textures::TEMPLATE_NATURAL;
	unsigned int Textures::TEMPLATE_ROUNDED;
	unsigned int Textures::TEMPLATE_SQUARED;

	unsigned int Textures::TILE_DIRT;
	unsigned int Textures::TILE_GRASS;
	unsigned int Textures::TILE_PURPLE_GRASS;
	unsigned int Textures::TILE_ANTIMATTER;
	unsigned int Textures::TILE_STONE;
	unsigned int Textures::TILE_AIR;

	static void loadImage(const char* filename, unsigned int &texture) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		texture = SOIL_load_OGL_texture
		(
			filename,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS
		);
		
	}

	void Textures::load() {
		loadImage("container.jpg", CONTAINER);
		loadImage("res/pixelinventor/textures/tiles/air.png", TILE_AIR);
		loadImage("res/pixelinventor/textures/tiles/dirt.png", TILE_DIRT);
		loadImage("res/pixelinventor/textures/tiles/antimatter.png", TILE_ANTIMATTER);
		loadImage("res/pixelinventor/textures/tiles/grass.png", TILE_GRASS);
		loadImage("res/pixelinventor/textures/tiles/stone.png", TILE_STONE);
		loadImage("res/pixelinventor/textures/tiles/purple_grass.png", TILE_PURPLE_GRASS);
		loadImage("res/pixelinventor/textures/tiles/templates/template_manmade.png", TEMPLATE_MANMADE);
		loadImage("res/pixelinventor/textures/tiles/templates/template_none.png", TEMPLATE_NONE);
		loadImage("res/pixelinventor/textures/tiles/templates/template_natural.png", TEMPLATE_NATURAL);
		loadImage("res/pixelinventor/textures/tiles/templates/template_squared.png", TEMPLATE_SQUARED);
		loadImage("res/pixelinventor/textures/tiles/templates/template_rounded.png", TEMPLATE_ROUNDED);
	}

	void Textures::dispose() {
		for (unsigned int i = 0; i < textures.size(); i++) {
			glDeleteTextures(1, textures.get(i));
		}
		textures.clear();
	}
}