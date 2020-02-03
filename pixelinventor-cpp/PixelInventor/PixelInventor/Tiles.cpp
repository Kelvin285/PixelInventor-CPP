#include "Tiles.h"
#include "Textures.h"
namespace PixelInventor {
	ArrayList<Tile> Tiles::tiles;
	Tile Tiles::AIR;
	Tile Tiles::DIRT;

	void Tiles::run() {
		AIR = Tile("pixelinventor:air", Textures::TILE_AIR);
		DIRT = GroundTile("pixelinventor:dirt", Textures::TILE_DIRT, 4, 4);
		AIR.setVisible(false);
		AIR.setLightValue(glm::vec3(1.0, 1.0, 1.0));
	}
}