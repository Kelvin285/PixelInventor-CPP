#include "TilePos.h"

TilePos::TilePos(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

TilePos::TilePos(double x, double y, double z) {
	this->x = (int)floor(x);
	this->y = (int)floor(y);
	this->z = (int)floor(z);
}

void TilePos::setPosition(int x, int y, int z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void TilePos::setPosition(double x, double y, double z) {
	this->x = (int)floor(x);
	this->y = (int)floor(y);
	this->z = (int)floor(z);
}

TilePos TilePos::add(int i, int j, int k) {
	return TilePos(x + i, y + j, z + k);
}

TilePos TilePos::add(double i, double j, double k) {
	return TilePos(x + i, y + j, z + k);
}

std::string TilePos::toString() {
	std::string str = "TilePos: [";
	str += x;
	str += ", ";
	str += y;
	str += ", ";
	str += z;
	str += "]";
	return str;
}