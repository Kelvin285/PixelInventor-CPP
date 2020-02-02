#pragma once
#include "ArrayList.h"
namespace PixelInventor {
	class Textures {
	public:
		static void load();
		static void dispose();

		static unsigned int CONTAINER;
		static unsigned int TEMPLATE_MANMADE;
		static unsigned int TEMPLATE_NONE;
		static unsigned int TEMPLATE_NATURAL;
		static unsigned int TEMPLATE_ROUNDED;
		static unsigned int TEMPLATE_SQUARED;

		static unsigned int TILE_DIRT;
		static unsigned int TILE_GRASS;
		static unsigned int TILE_PURPLE_GRASS;
		static unsigned int TILE_ANTIMATTER;
		static unsigned int TILE_STONE;
		static unsigned int TILE_AIR;
		static ArrayList<unsigned int*> textures;
	};
}