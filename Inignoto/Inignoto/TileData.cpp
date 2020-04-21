#include "TileData.h"

TileData::TileData() {
	this->setTile(Tiles::AIR.getID());
}

TileData::TileData(int tile)
{
	this->setTile(tile);
}

int TileData::getTile() {
	return tile;
}

void TileData::setTile(int tile) {
	this->tile = tile;
}

float TileData::getMiningTime() {
	return miningTime;
}

void TileData::setMiningTime(float miningTime) {
	this->lastMiningTime = this->miningTime;
	this->miningTime = miningTime;
}

float TileData::getLastMiningTime() {
	return this->lastMiningTime;
}

int TileData::getWaterLevel() {
	return this->waterLevel;
}

void TileData::setWaterLevel(int waterLevel) {
	this->waterLevel = waterLevel;
}