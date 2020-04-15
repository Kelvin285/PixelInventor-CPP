#pragma once
#include <string>
class TileData
{
public:
	TileData(int tile);
	int getTile();
	void setTile(int tile);
	float getMiningTime();
	void setMiningTime(float miningTime);
	float getLastMiningTime();
	int getWaterLevel();
	void setWaterLevel(int waterLevel);
private:
	int tile;
	float miningTime;
	int waterLevel;
	float lastMiningTime;
};
