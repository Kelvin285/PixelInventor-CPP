#include "Tile.h"
#include "Tiles.h"

int Tile::CURRENT_ID = 0;

Tile::Tile(std::string modid, std::string name) {
	this->name = name;
	std::string dir = "assets/" + modid + "/models/tiles/" + name + ".model";
	std::ifstream t(dir);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	std::unordered_map<std::string, std::string> data = Utils::getData(str);
	t.close();
	for (auto at : data) {
		std::string a = at.first;
		std::string b = at.second;
		if (a == "num_x") width = Utils::getInt(b);
		if (a == "num_y") height = Utils::getInt(b);
		if (a == "texture") texture = b;
		if (a == "side") side_texture = b;
		if (a == "top") top_texture = b;
		if (a == "bottom") bottom_texture = b;
		if (a == "left") left_texture = b;
		if (a == "right") right_texture = b;
		if (a == "front") front_texture = b;
		if (a == "back") back_texture = b;
	}
	
	ID = CURRENT_ID++;
	std::cout << "ID: " << ID << std::endl;
}

int Tile::getID()
{
	return this->ID;
}

std::string Tile::getTranslatedName() {
	return Translation::translateText(getName());
}
Tile* Tile::setHardness(float hardness) {
	this->hardness = hardness;
	return this;
}
Tile* Tile::setFullCube(bool fullCube) {
	this->isFullCube = fullCube;
	return this;
}
Tile* Tile::setReplaceable() {
	this->isReplaceable = true;
	return this;
}
Tile* Tile::setBlocksMovement(bool blocksMovement) {
	this->blocksMovement = true;
	return this;
}
Tile* Tile::setRayTraceType(TileRayTraceType rayTraceType) {
	this->rayTraceType = rayTraceType;
	return this;
}
Tile* Tile::setVisible(bool visible) {
	this->visible = visible;
	return this;
}
std::string Tile::getTextureFor(BlockFace face) {
	if (face == BlockFace::LEFT) {
		if (left_texture.empty()) return getSideTexture();
		return left_texture;
	}
	if (face == BlockFace::RIGHT) {
		if (right_texture.empty()) return getSideTexture();
		return right_texture;
	}
	if (face == BlockFace::FRONT) {
		if (front_texture.empty()) return getSideTexture();
		return front_texture;
	}
	if (face == BlockFace::BACK) {
		if (back_texture.empty()) return getSideTexture();
		return back_texture;
	}
	if (face == BlockFace::UP) {
		if (top_texture.empty()) return texture;
		return top_texture;
	}
	if (face == BlockFace::DOWN) {
		if (bottom_texture.empty()) return texture;
		return bottom_texture;
	}
	return texture;
}
std::string Tile::getSideTexture() {
	if (side_texture.empty()) return texture;
	return side_texture;
}