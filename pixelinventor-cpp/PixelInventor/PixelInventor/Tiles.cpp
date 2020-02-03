#include "Tiles.h"
#include "Textures.h"
namespace PixelInventor {
	ArrayList<Tile> Tiles::tiles;
	Tile Tiles::AIR;
	GroundTile Tiles::DIRT;
	GroundTile Tiles::GRASS;
	GroundTile Tiles::PURPLE_GRASS;

	void Tiles::run() {
		AIR = Tile("pixelinventor:air", Textures::TILE_AIR);
		AIR.setVisible(false);
		AIR.setLightValue(glm::vec3(1.0, 1.0, 1.0));
		DIRT = GroundTile("pixelinventor:dirt", Textures::TILE_DIRT, 4, 4);
		GRASS = GroundTile("pixelinventor:grass", Textures::TILE_DIRT, 4, 4);
		GRASS.setOverlay(Textures::TILE_GRASS);
		GRASS.setLightValue(glm::vec3(0.0, 0.5, 0.0));
		GRASS.setTilingTemplate(Textures::TEMPLATE_NATURAL);
		PURPLE_GRASS = GroundTile("pixelinventor:purple_grass", Textures::TILE_DIRT, 4, 4);
		PURPLE_GRASS.setOverlay(Textures::TILE_PURPLE_GRASS);
		PURPLE_GRASS.setLightValue(glm::vec3(0.5, 0.0, 0.5));
		PURPLE_GRASS.setTilingTemplate(Textures::TEMPLATE_NATURAL);
	}
}