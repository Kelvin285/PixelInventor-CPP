#pragma once
#include <string>
#include "Textures.h"
#include "Utils.h"
#include <unordered_map>
#include "BlockFace.h"
#include "Translation.h"

enum TileRayTraceType {
	SOLID, LIQUID, GAS
};

class Tile
{
private:
	std::string name;
	bool fullCube = true;
	bool visible = true;
	bool blocksMovement = true;
	bool isReplaceable = true;

	std::string texture = "";
	std::string side_texture = "";
	std::string front_texture = "";
	std::string back_texture = "";
	std::string left_texture = "";
	std::string right_texture = "";
	std::string top_texture = "";
	std::string bottom_texture = "";
	int width = 1;
	int height = 1;

	static int CURRENT_ID;
	int ID;

	float hardness;

	TileRayTraceType rayTraceType = TileRayTraceType::SOLID;


public:
	Tile(std::string modid, std::string name);

	TileRayTraceType getRayTraceType() { return rayTraceType; }
	int getID() { return ID; }
	std::string getName() { return name; }
	float getHardness() { return hardness; }

	bool isFullCube() { return isFullCube; }
	bool blocksMovement() { return blocksMovement; }
	bool isVisible() { return visible; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	bool isReplaceable() { return isReplaceable; }

	std::string getTranslatedName();
	Tile* setHardness(float hardness);
	Tile* setFullCube(bool fullCube);
	Tile* setReplaceable();
	Tile* setBlocksMovement(bool blocksMovement);
	Tile* setRayTraceType(TileRayTraceType rayTraceType);
	Tile* setVisible(bool visible);
	std::string getTextureFor(BlockFace face);
	std::string getSideTexture();

	//TODO: virtual void dropAsItem(World* world, int x, int y, int z);

	//TODO: virtual void tick(World* world, TilePos* pos, Random* random);

	double virtual getTickPercent() { return 0; }
};

